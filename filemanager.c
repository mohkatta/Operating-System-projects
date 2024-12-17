#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

/*
stdio.h: Provides standard input/output functions like printf, fopen, fclose, etc.
stdlib.h: Provides general utility functions like malloc, free, exit, etc.
string.h: Provides string manipulation functions like strcmp, strcpy, etc.
unistd.h: Provides system calls like access, chmod, etc.
sys/stat.h: Defines structures for file status information, such as struct stat.
dirent.h: Defines structures and functions for directory operations.
errno.h: Defines error codes that can be used to diagnose errors.
*/

void list_files(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Files and directories in '%s':\n", path);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

void change_permissions(const char *filepath, mode_t mode) {
    if (chmod(filepath, mode) < 0) {
        perror("chmod");
    } else {
        printf("Changed permissions for '%s' to %03o\n", filepath, mode);
    }
}

void create_file(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file) {
        fclose(file);
        printf("File '%s' created successfully.\n", filepath);
    } else {
        perror("fopen");
    }
}

void delete_file(const char *filepath) {
    if (remove(filepath) < 0) {
        perror("remove");
    } else {
        printf("File '%s' deleted successfully.\n", filepath);
    }
}

void create_directory(const char *dirname) {
    if (mkdir(dirname, 0755) < 0) {
        perror("mkdir");
    } else {
        printf("Directory '%s' created successfully.\n", dirname);
    }
}

void delete_directory(const char *dirname) {
    if (rmdir(dirname) < 0) {
        perror("rmdir");
    } else {
        printf("Directory '%s' deleted successfully.\n", dirname);
    }
}

void create_symlink(const char *target, const char *linkpath) {
    if (symlink(target, linkpath) < 0) {
        perror("symlink");
    } else {
        printf("Symbolic link '%s' created -> '%s'.\n", linkpath, target);
    }
}

void rename_file(const char *oldname, const char *newname) {
    if (rename(oldname, newname) < 0) {
        perror("rename");
    } else {
        printf("Renamed '%s' to '%s'.\n", oldname, newname);
    }
}

void display_help() {
    printf("File Manager Help:\n");
    printf("This program allows you to manage files and directories with the following options:\n");
    printf("1. List files/directories\n");
    printf("2. Change permissions of a file\n");
    printf("3. Create a file\n");
    printf("4. Delete a file\n");
    printf("5. Create a directory\n");
    printf("6. Delete a directory\n");
    printf("7. Create a symbolic link\n");
    printf("8. Rename a file/directory\n");
    printf("9. Exit the program\n");
}

void display_manual() {
    printf("NAME\n");
    printf("    file_manager - a simple file manager\n");
    printf("SYNOPSIS\n");
    printf("    file_manager [OPTION]\n");
    printf("DESCRIPTION\n");
    printf("    This program provides basic file management functionalities including:\n");
    printf("    - Listing files and directories\n");
    printf("    - Changing file permissions\n");
    printf("    - Creating and deleting files and directories\n");
    printf("    - Creating symbolic links\n");
    printf("    - Renaming files and directories\n");
    printf("OPTIONS\n");
    printf("    --help, -h\n");
    printf("        Display this help message.\n");
    printf("    man\n");
    printf("        Show the manual page for file_manager.\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            display_help();
            return 0;
        } else if (strcmp(argv[1], "man") == 0) {
            display_manual();
            return 0;
        }
    }

    int choice;
    char path[256], target[256], link[256], oldname[256], newname[256];
    mode_t mode;

    while (1) {
        printf("\nFile Manager Menu:\n");
        printf("1. List files/directories\n");
        printf("2. Change permissions\n");
        printf("3. Create file\n");
        printf("4. Delete file\n");
        printf("5. Create directory\n");
        printf("6. Delete directory\n");
        printf("7. Create symbolic link\n");
        printf("8. Rename file/directory\n");
        printf("9. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printf("Enter directory path: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0; // Remove newline
                list_files(path);
                break;
            case 2:
                printf("Enter file path: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;
                printf("Enter new permissions (in octal, e.g., 755): ");
                scanf("%o", &mode);
                change_permissions(path, mode);
                break;
            case 3:
                printf("Enter file name to create: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;
                create_file(path);
                break;
            case 4:
                printf("Enter file name to delete: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;
                delete_file(path);
                break;
            case 5:
                printf("Enter directory name to create: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;
                create_directory(path);
                break;
            case 6:
                printf("Enter directory name to delete: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0;
                delete_directory(path);
                break;
            case 7:
                printf("Enter target file: ");
                fgets(target, sizeof(target), stdin);
                target[strcspn(target, "\n")] = 0;
                printf("Enter name for symbolic link: ");
                fgets(link, sizeof(link), stdin);
                link[strcspn(link, "\n")] = 0;
                create_symlink(target, link);
                break;
            case 8:
                printf("Enter old name: ");
                fgets(oldname, sizeof(oldname), stdin);
                oldname[strcspn(oldname, "\n")] = 0;
                printf("Enter new name: ");
                fgets(newname, sizeof(newname), stdin);
                newname[strcspn(newname, "\n")] = 0;
                rename_file(oldname, newname);
                break;
            case 9:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
