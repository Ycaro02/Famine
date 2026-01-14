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

/* Woody_Woopacker main function called in main */
s8 woody_woodpacker(UserInput *input) {
	ElfFile		*f = NULL;
	WoodyData	woody = {0};
	Payload		payload = {0};

	payload.input = input;

	/* Init the woody woodpacker data */
	if (!(f = woody_woodpacker_init(input->path, &payload, &woody))) {
		input_destroy(input);
		return (1);
	} 
	
	/* Generate the key */
	if (has_flag(input->flag, FLAG_KEY)) {
		if (!(woody.encrypt_key = fill_hexa_buff(input->key, input->key_len))) {
			goto free_rsc;
			return (1);
		}
	} else if (!(woody.encrypt_key = keygen(input->key_len))) {
		goto free_rsc;
		return (1);
	}


	/* Inject the payload and create new file*/
	inject_payload(f, &woody, &payload);


	free(woody.encrypt_key);
	free_rsc:
		free(woody.ptr);
		free(payload.code);
		elf_file_destroy(f);	
		input_destroy(input);
	return (0);
}