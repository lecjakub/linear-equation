/*! @file argparser.h
 * @brief class to manage arguments
 * */
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <stdbool.h>
#include <libconfig.h>

/*!
 * A structure to parsing aplication arguments
*/
typedef struct argparser{
    int *argc; /*!< pointer to variable containing number of arguments*/
    char** argv;/*!< pointer to table of arguments*/
} argparser_t;

/*
 * @brief argparser constructor
 * @param int* argc pointer to variable containing number of arguments
 * @param char** argv table of arguments
 * @return pointer to argparser or NULL on failure
*/
argparser_t* argparser_init( int*argc, char** argv);

/*!
 * @brief main method to parsing arguments
 * @param argparser *argparser instance of argparser
 * @return configuration struct
 * 
*/
config_t* argparser_parse_args(argparser_t *argparser);



#endif ARGPARSER_H
