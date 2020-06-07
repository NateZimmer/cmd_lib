#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum{
    TYPE_NULL, // No data, for callback cmds  
    TYPE_UINT32, // Type uint32_t
    TYPE_UINT8 // Type uint8_t
}type_t;


typedef struct{
    void (*read_cb)(); // Read callback 
    void (*write_cb)(); // Write callback 
    type_t type; // Type of data 
    void * val; // Ptr to data 
    const char cmd_str[20]; // Name of data 
}cmd_t; 

#define cmd_print printf // Define your own print system here 


// Command functions 
void parse_cmd(char * cmd_str, uint16_t cmd_size);
void list_cmds(uint16_t cmd_size);