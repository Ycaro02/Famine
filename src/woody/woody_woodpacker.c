#include <woody.h>
#include <elf_getter.h>
#include <parse_flag.h>

static ElfFile *woody_woodpacker_init(char *path, Payload *payload, WoodyData *woody) {
	ElfFile	*f = NULL;
	
	if (!(f = elf_file_get(path))) {
		return (NULL);
	} else if (!payload_build(payload, f->is_64)) {
		elf_file_destroy(f);	
		return (NULL);
	} else if (!segment_load(f)) {
		elf_file_destroy(f);
		free(payload->code);	
		return (NULL);
	}

	LOG(L_INFO, GREEN"File: %s\n"RESET, path);

	/* Create the woody data */
	woody->size = woody_size_compute(f, payload);
	woody->size += f->total_shsize + f->shstrtab->size;
	if (!(woody->ptr = ft_calloc(woody->size, 1))) {
		elf_file_destroy(f);
		free(payload->code);	
		return (NULL);
	}
	return (f);
}

void input_destroy(UserInput *input) {
	if (input->path) {
		free(input->path);
	}
	if (input->arg) {
		free(input->arg);
	}
	if (input->key) {
		free(input->key);
	}
}



void file_sync(char *filename, char *data, ssize_t filesize) {

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("stat");
        return ;
    }

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        return ;
    } else if (ftruncate(fd, (off_t)filesize) == -1) {
        perror("ftruncate");
        close(fd);
        return ;
    }

    void *map = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return ;
    }

    ft_memcpy(map, data, filesize);

    if (msync(map, filesize, MS_SYNC) == -1) {
        ERR("msync failed\n");
        perror("msync");
    } else if (munmap(map, filesize) == -1) {
        perror("munmap");
    }

    INFO("File synced successfully: %s\n", filename);

    close(fd);

    return ;
}


/* Woody_Woopacker main function called in main */
s8 woody_woodpacker(UserInput *input) {
	ElfFile		*f = NULL;
	WoodyData	woody = {0};
	Payload		payload = {0};

	payload.input = input;

	/* Init the woody woodpacker data */
	if (!(f = woody_woodpacker_init(input->path, &payload, &woody))) {
		return (1);
	} 
	
	/* Generate the key */
	if (has_flag(input->flag, FLAG_KEY)) {
		if (!(woody.encrypt_key = fill_hexa_buff(input->key, input->key_len))) {
			goto free_rsc;
		}
	} else if (!(woody.encrypt_key = keygen(input->key_len))) {
		goto free_rsc;
	}

    
    if (search_interp_phdr(f) == FALSE) {
        ERR("No PT_INTERP Segment found, protect against dynamic lib injection\n");
        goto free_rsc;
    } else if (ft_strnstr(input->path, ".so", ft_strlen(input->path))) {
        ERR("File is a shared object, protect against dynamic lib injection\n");
        goto free_rsc;
    }
    
	/* Inject the payload and create new file*/
	if (!inject_payload(f, &woody, &payload)) {
		ERR("Failed to inject payload\n");
		goto free_rsc;
	}

    file_sync(input->path, woody.ptr, woody.size);

	free_rsc:
		free(woody.ptr);
		free(payload.code);
        free(woody.encrypt_key);
		elf_file_destroy(f);	
	return (0);
}