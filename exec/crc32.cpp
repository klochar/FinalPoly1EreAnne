#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



uint32_t generate_crc32 (uint32_t crc, unsigned char *data, int length) { 
    int i, j; 
    for (i=0; i<length; i++) { 
        crc = crc ^ *(data++); 
        for (j=0; j<8; j++) { 
		    if (crc & 1) 
		        crc = (crc>>1) ^ 0xEDB88320 ; 
		    else 
		        crc = crc >>1 ; 
        } 
    } 
    return crc; 
}
int main() {
    FILE *file;
    unsigned char *data;
    long file_size;
    uint32_t crc32;

    // Ouvrir le fichier en mode lecture binaire
    file = fopen("svg.txt", "rb");
    if (!file) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Obtenir la taille du fichier
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allouer de la mémoire pour le tampon et lire le contenu du fichier
    data = (unsigned char *)malloc(file_size);
    if (!data) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        fclose(file);
        return 1;
    }
    fread(data, 1, file_size, file);
    fclose(file);

    // Calculer le CRC-32 du contenu du fichier
    crc32 = generate_crc32(0, data, file_size);
    printf("Le CRC-32 du fichier est: 0x%08X\n", crc32);

    // Libérer la mémoire
    free(data);

    return 0;
}

