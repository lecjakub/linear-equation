/*! @file core.c
 * @brief application core
 * this file is application core
*/
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include "argparser.h"

int main(int argc, char** argv){

    argparser_t *argpar;
    //initiating parser
    argpar = argparser_init(&argc, argv);

    //generating configuration
    config_t *config;
    config = argparser_parse_args(argpar);


    printf("Hello from core moduleasdf!\n");
    //declaring 8 element array
    int* ar = (int*)malloc(sizeof(int) * 8);
    //printf("size of array: %d", sizeof(ar) );
    printf("size of float: %d", sizeof(float));
}
