
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Project configuration
#define DB_FILE "database.txt"
#define HASH_SIZE 65
#define PATH_SIZE 4096
#define LINE_SIZE (HASH_SIZE + PATH_SIZE + 4)

// Remove newline characters
void remove_newline(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

// Get file path from user
int get_file_path(char *path)
{
    printf("\nEnter file path: ");

    if (fgets(path, PATH_SIZE, stdin) == NULL)
        return 0;

    remove_newline(path);

    if (path[0] == '\0') {
        printf("File path cannot be empty.\n");
        return 0;
    }

    if (strchr(path, '|') != NULL) {
        printf("File path cannot contain | character.\n");
        return 0;
    }

    return 1;
}

// Generate SHA-256 hash using OpenSSL
int calculate_hash(const char *filename, char *hash)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Unable to open file");
        return 0;
    }

    EVP_MD_CTX *context = EVP_MD_CTX_new();

    if (context == NULL) {
        fclose(file);
        printf("Hash context creation failed.\n");
        return 0;
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), NULL) != 1) {
        printf("SHA-256 initialization failed.\n");
        EVP_MD_CTX_free(context);
        fclose(file);
        return 0;
    }

    unsigned char buffer[4096];
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_length = 0;
    size_t bytes;

    // Read file in chunks
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {

        if (EVP_DigestUpdate(context, buffer, bytes) != 1) {
            printf("Hash update failed.\n");
            EVP_MD_CTX_free(context);
            fclose(file);
            return 0;
        }
    }

    if (ferror(file)) {
        printf("File reading error.\n");
        EVP_MD_CTX_free(context);
        fclose(file);
        return 0;
    }

    if (EVP_DigestFinal_ex(context, digest, &digest_length) != 1) {
        printf("Hash generation failed.\n");
        EVP_MD_CTX_free(context);
        fclose(file);
        return 0;
    }

    // Convert binary hash into hexadecimal string
    for (unsigned int i = 0; i < digest_length; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }

    hash[digest_length * 2] = '\0';

    EVP_MD_CTX_free(context);
    fclose(file);

    return 1;
}

// Register a file
void register_file()
{
    char path[PATH_SIZE];
    char hash[HASH_SIZE];

    if (!get_file_path(path))
        return;

    if (!calculate_hash(path, hash))
        return;

    FILE *db = fopen(DB_FILE, "a");

    if (db == NULL) {
        perror("Unable to open database");
        return;
    }

    if (fprintf(db, "%s|%s\n", hash, path) < 0) {
        printf("Error writing database.\n");
        fclose(db);
        return;
    }

    fclose(db);

    printf("\n====================================\n");
    printf("       FILE REGISTERED SUCCESSFULLY\n");
    printf("====================================\n");

    printf("File: %s\n", path);
    printf("SHA-256: %s\n", hash);
}

// Verify file integrity
void verify_file()
{
    char path[PATH_SIZE];
    char current_hash[HASH_SIZE];
    char stored_hash[HASH_SIZE];
    char line[LINE_SIZE];

    int found = 0;

    if (!get_file_path(path))
        return;

    if (!calculate_hash(path, current_hash))
        return;

    FILE *db = fopen(DB_FILE, "r");

    if (db == NULL) {
        printf("\nNo registered files found.\n");
        return;
    }

    // Search for the registered file
    // The latest registration is used
    while (fgets(line, sizeof(line), db) != NULL) {

        char *separator = strchr(line, '|');

        if (separator == NULL)
            continue;

        *separator = '\0';

        char *stored_path = separator + 1;
        remove_newline(stored_path);

        if (strcmp(path, stored_path) == 0) {

            strncpy(stored_hash, line, HASH_SIZE - 1);
            stored_hash[HASH_SIZE - 1] = '\0';

            found = 1;
        }
    }

    fclose(db);

    if (!found) {
        printf("\nFile not registered!\n");
        printf("Register the file before verification.\n");
        return;
    }

    printf("\n====================================\n");
    printf("          INTEGRITY REPORT\n");
    printf("====================================\n");

    printf("File: %s\n", path);
    printf("Stored Hash : %s\n", stored_hash);
    printf("Current Hash: %s\n", current_hash);

    if (strcmp(stored_hash, current_hash) == 0) {

        printf("\n[PASS] FILE INTEGRITY VERIFIED!\n");
        printf("The file has not changed since registration.\n");

    } else {

        printf("\n[WARNING] FILE MODIFIED!\n");
        printf("The file content has changed.\n");
    }
}

// View registered files
void view_records()
{
    char line[LINE_SIZE];
    int count = 0;

    FILE *db = fopen(DB_FILE, "r");

    if (db == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\n========== REGISTERED FILES ==========\n");

    while (fgets(line, sizeof(line), db) != NULL) {

        char *separator = strchr(line, '|');

        if (separator == NULL)
            continue;

        *separator = '\0';

        char *path = separator + 1;
        remove_newline(path);

        printf("\nFile: %s\n", path);
        printf("SHA-256: %s\n", line);

        count++;
    }

    fclose(db);

    printf("\nTotal registered records: %d\n", count);
}

// Main function
int main()
{
    int choice;
    char input[32];

    printf("\n");
    printf("========================================\n");
    printf("       FILEGUARD - INTEGRITY CHECKER\n");
    printf("========================================\n");

    while (1) {

        printf("\n1. Register a file");
        printf("\n2. Verify file integrity");
        printf("\n3. View registered files");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (strchr(input, '\n') == NULL) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }

        if (sscanf(input, "%d", &choice) != 1) {
            printf("\nInvalid input! Enter a number.\n");
            continue;
        }

        switch (choice) {

            case 1:
                register_file();
                break;

            case 2:
                verify_file();
                break;

            case 3:
                view_records();
                break;

            case 4:
                printf("\nThank you for using FileGuard!\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
