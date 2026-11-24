#include "libopencm3/stm32/rcc.h"   //Needed to enable clocks for particular GPIO ports
#include "libopencm3/stm32/gpio.h"  //Needed to define things on the GPIO




int main(void) {

    int LeftPaddle = 18;
    int RightPaddle = 18;

    rcc_periph_clock_enable(RCC_GPIOC); //Enable clock for GPIO Port A
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO2);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO3);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO4);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO5);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO6);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO7);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);            //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO8);
              //GPIO Port Name, GPIO Mode, GPIO Push Up Pull Down Mode, GPIO Pin Number
   
    //setting row 3 cell 3
    ClearBoard();

    gpio_clear(GPIOC, GPIO8);
    
    gpio_clear(GPIOC,GPIO2);
    gpio_clear(GPIOC,GPIO3);
    gpio_clear(GPIOC,GPIO4);
    gpio_clear(GPIOC,GPIO5);
    
    // TurnWhiteLightOn(3,6);

    MakePaddles();
    gpio_set(GPIOC, GPIO8);
  
        


    return 0;
}


int TurnWhiteLight(int row, int Column){
    bool Extra = false;
    if (row > 16){
        row = row - 16;
        Extra = true;
    }
    Row(row);
    Set();
    int i;
    for (i = 0; i < 31; i++){
        Clear();
    }
    Set();
    for (i = 0; i < 31; i++){
        Clear();
    }
    Set();
    
    for(i = 0; i< Column; i++){
        Clear();
    }
    
     if (Extra){
        int j;
        for (j = 0; j < 32*3; j++){
            Clear();
        }
    }
}




int TurnRedLightOn(int row, int Column){
    bool Extra = false;
    if (row > 16){
        row = row - 16;
        Extra = true;
    }
    Row(row);
    Set();
    int i =0;
    for (i = 0; i < Column; i++){
        Clear();
    }
    if (Extra){
        int j;
        for (j = 0; j < 32*3; j++){
            Clear();
        }
    }
}


int Clear(){
    gpio_clear(GPIOC,GPIO7);
    gpio_clear(GPIOC, GPIO6);
    gpio_set(GPIOC,GPIO7);
    return 0;
}


int Set(){
    gpio_clear(GPIOC,GPIO7);
    gpio_set(GPIOC, GPIO6);
    gpio_set(GPIOC,GPIO7);
    return 0;
}

int Row(int Row){
    if (Row - 8 >= 0){
        gpio_set(GPIOC,GPIO5);
        Row = Row - 8;
    }
    if (Row - 4 >= 0){
        gpio_set(GPIOC,GPIO4);
        Row = Row - 4;
    }
    if (Row - 2 >= 0){
        gpio_set(GPIOC,GPIO3);
        Row = Row - 2;
    }
    if (Row - 1 >= 0){
        gpio_set(GPIOC,GPIO2);
        Row = Row - 1;
    }

}

int ClearBoard(){
    int i = 0;
    for (i = 0 ; i < 16*192; i++){
        Clear();
    }
}

int MakePaddles(){
    int i;
    for (i = 18; i < 23; i++){
        
        TurnWhiteLight(i,1);
        TurnWhiteLight(i,32);
    }
}


int Pulses(int num){
    while (num != 0){
        if (num % 2 == 0){
            Clear();
        }
        else{
            Set();
        }
        num = num >> 2;
    }
    
}

int PickRowThenPulse(int row, int num){
    bool Extra = false;
    if (row > 16){
        row = row - 16;
        Extra = true;
    }
    Row(row);
    Pulses(num);
    if (Extra){
        int j;
        for (j = 0; j < 32*3; j++){
            Clear();
        }
    }
}

