# cmd_lib

A basic c lib for writing/reading program commands 

```c
#include <stdio.h>
#include "cmd_lib.h"

void goodbye_cb(){
    printf("Goodbye");
}

uint32_t myVal = 0;

cmd_t cmd_array[] = {
    {
//      .write_cb = my_write_cb, // optional 
//      .read_cb = my_read_cb // optional 
        .cmd_str = "Hello",
        .val = &myVal,
        .type = TYPE_UINT32
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
```

Output example: 

```console
Command list:                                  
Hello                                          
Goodbye                                         
Type your command below                       
Hello                                          
$Hello,0,OK                                       
Hello=2 
$Hello,2,OK
```

### How it works: 

Specify a `cmd_array` with a list of your commands. Call `parse_cmd` when a command string has been entered. 