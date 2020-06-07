#include <stdio.h>
#include "cmd_lib.h"

void goodbye_cb(){
    printf("Goodbye");
}

int myVal = 0;

cmd_t cmd_array[] = {
    {
//      .write_cb = my_write_cb, // optional 
//      .read_cb = my_read_cb // optional 
        .cmd_str = "Hello",
        .val = &myVal,
        .type = TYPE_UINT
    },
    {
        .read_cb = goodbye_cb,
        .cmd_str = "Goodbye"
    }
};
uint16_t cmd_size = sizeof(cmd_array)/sizeof(cmd_array[0]);

char in_buf[50];

int main()
{
    printf("Command list:\r\n");
    list_cmds(cmd_size);
    printf("Type your command below\r\n");
    while(1){
        scanf("%s",in_buf);
        parse_cmd(in_buf,cmd_size);
    }
}

