#include "cmd_lib.h"

// To be externally defined 
extern cmd_t cmd_array[];

char cmd_out_buffer[50];


void read_cmd(cmd_t * cmd,bool call_cb){
    
    if( (cmd->read_cb != NULL) && call_cb ){
        cmd->read_cb();
    } 
    
    if(cmd->val == NULL){ // Return if not set 
        return; 
    }
    
    switch(cmd->type)
    {
        case TYPE_UINT32:
            sprintf(cmd_out_buffer,"$%s,%i,OK\r\n",cmd->cmd_str,*((uint32_t *)cmd->val));
            break;
        case TYPE_UINT8:
            sprintf(cmd_out_buffer,"$%s,%i,OK\r\n",cmd->cmd_str,*((uint8_t *)cmd->val));
            break;
        default:
            break;
    }
    cmd_print(cmd_out_buffer);
}


void write_cmd(cmd_t * cmd, char * data){
    char * end_ptr;
    bool invalid_write = true; 
    // Return if not set
    if( (cmd->val == NULL) || (cmd->type == TYPE_NULL)){ 
        cmd_print("[ERROR] Invalid Setup"); 
        return; 
    }
    data++; // Increment to value 
    
    uint32_t temp_u_val = 0; 
    
    switch(cmd->type)
    {
        case TYPE_UINT32:
            temp_u_val = (uint32_t)strtol(data,&end_ptr,0);
            if(*end_ptr == 0){
                *((uint32_t *)cmd->val) = temp_u_val;
                read_cmd(cmd,false);
                invalid_write = false; 
            }
            break;
        case TYPE_UINT8:
            temp_u_val = (uint8_t)strtol(data,&end_ptr,0);
            if(*end_ptr == 0){
                *((uint8_t *)cmd->val) = temp_u_val;
                read_cmd(cmd,false);
                invalid_write = false; 
            }
            break;
        default:
            break;
    }
    if(invalid_write){
        cmd_print("[ERROR] Invalid Write");
    }else{
        if(cmd->write_cb){
            cmd->write_cb();
        }       
    }
}


void cmd_proccess(cmd_t * cmd, char * data){
    char * cmd_char = data + strlen(cmd->cmd_str);
    
    switch(*cmd_char){
        case '\n':
        case '\r':
        case 0:
        case '?':
            read_cmd(cmd,true);
            break;
        case '=':
            write_cmd(cmd,cmd_char);
            break;
        default:
            cmd_print("char val %i",(int)(*cmd_char));
            break;
    }
}


void parse_cmd(char * cmd_str, uint16_t cmd_size){
    bool cmd_found = false; 
    char * cmd_ptr;
    // For each CMD in array 
    for(uint16_t i = 0; i < cmd_size; i++){
        cmd_t * cmd = &cmd_array[i];
        // Check string for cmd_str 
        cmd_ptr = strstr(cmd_str,cmd->cmd_str);
        if(cmd_ptr != NULL){ // IF CMD found 
            cmd_proccess(cmd,cmd_ptr);
            cmd_found = true;
            break;  
        }
    }
    if(!cmd_found){
        cmd_print("Error, CMD not found\r\n");
    }
}


void list_cmds(uint16_t cmd_size){
    for(uint16_t i = 0; i < cmd_size; i++){
        cmd_t * cmd = &cmd_array[i];
        cmd_print(cmd->cmd_str);
        cmd_print("\r\n");
    }
}