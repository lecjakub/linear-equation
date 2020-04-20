#include "argparser.h"
#include <stdlib.h>

argparser_t* argparser_init( int*argc, char** argv){
    argparser_t* new_argparser = (argparser_t*)malloc(sizeof(argparser_t));
    return new_argparser;
}

config_t* argparser_parse_args(argparser_t *argparser){
    config_t* conf = (config_t*)malloc(sizeof(config_t));
    config_read_string(conf,"[asdf]");
    return conf;
}
