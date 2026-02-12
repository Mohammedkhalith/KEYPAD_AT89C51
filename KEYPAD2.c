#include <reg51.h>

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;
sbit C1 = P3^4;
sbit C2 = P3^5;
sbit C3 = P3^6;
sbit C4 = P3^7;

sbit rs = P1^0;
sbit rw = P1^1;
sbit en = P1^2;
#define lcd_data P2

int a = 0, b = 0, res = 0;
char c = 0;
bit flag = 0; 


void lcd_delay(unsigned int d) {
    unsigned int i, j;
    for (i = 0; i < d; i++) {
        for (j = 0; j < 1275; j++);
    }
}

void cmd(unsigned char a) {
    lcd_data = a;
    rs = 0;
    rw = 0;
    en = 1;
    lcd_delay(2);
    en = 0;
}

void dat(unsigned char b) {
    lcd_data = b;
    rs = 1;
    rw = 0;
    en = 1;
    lcd_delay(5);
    en = 0;
}

void lcd_init() {
    lcd_delay(10);
    cmd(0x38); 
    cmd(0x0C); 
    cmd(0x06); 
    cmd(0x01); 
    lcd_delay(2);
}

void show(unsigned char *s) {
    while (*s) {
        dat(*s++);
    }
}


void print_number(int num) {
    char buffer[6];
    int i = 0, j;

    if (num == 0) {
        dat('0');
        return;
    }

    if (num < 0) {
        dat('-');
        num = -num;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (j = i - 1; j >= 0; j--) {
        dat(buffer[j]);
    }
}


void process_key(char key) {
    dat(key); 

    if (key >= '0' && key <= '9') {
        if (flag == 0) {
            a = a * 10 + (key - '0');
        } else {
            b = b * 10 + (key - '0');
        }
    } else if (key == '+' || key == '-' || key == 'X' || key == '/') {
        c = key;
        flag = 1;
    } else if (key == '=') {
        switch (c) {
            case '+': res = a + b; 
					  break;
            case '-': res = a - b; 
					  break;
            case 'X': res = a * b; 
					  break;
            case '/': res = (b != 0) ? a / b : 0; 
					  break;
        }
				
        cmd(0x01); 
        lcd_delay(2);
        print_number(res);
    }
}


void row_1() {
    R1 = 0; R2 = R3 = R4 = 1;
    C1 = C2 = C3 = C4 = 1;

    if (C1 == 0) {
        process_key('7');
        while (C1 == 0);
    } else if (C2 == 0) {
        process_key('8');
        while (C2 == 0);
    } else if (C3 == 0) {
        process_key('9');
        while (C3 == 0);
    } else if (C4 == 0) {
        process_key('/');
        while (C4 == 0);
    }
}


void row_2() {
    R2 = 0; R1 = R3 = R4 = 1;
    C1 = C2 = C3 = C4 = 1;

    if (C1 == 0) {
        process_key('4');
        while (C1 == 0);
    } else if (C2 == 0) {
        process_key('5');
        while (C2 == 0);
    } else if (C3 == 0) {
        process_key('6');
        while (C3 == 0);
    } else if (C4 == 0) {
        process_key('X');
        while (C4 == 0);
    }
}


void row_3() {
    R3 = 0; R1 = R2 = R4 = 1;
    C1 = C2 = C3 = C4 = 1;

    if (C1 == 0) {
        process_key('1');
        while (C1 == 0);
    } else if (C2 == 0) {
        process_key('2');
        while (C2 == 0);
    } else if (C3 == 0) {
        process_key('3');
        while (C3 == 0);
    } else if (C4 == 0) {
        process_key('-');
        while (C4 == 0);
    }
}

void row_4() {
    R4 = 0; R1 = R2 = R3 = 1;
    C1 = C2 = C3 = C4 = 1;

    if (C1 == 0) {
        cmd(0x01); 
        lcd_delay(2);
        
        while (C1 == 0);
    } else if (C2 == 0) {
        process_key('0');
        while (C2 == 0);
    } else if (C3 == 0) {
        process_key('=');
        while (C3 == 0);
    } else if (C4 == 0) {
        process_key('+');
        while (C4 == 0);
    }
}


void main() {
    lcd_init();
    cmd(0x01); 
    while (1) {
        row_1();
        row_2();
        row_3();
        row_4();
    }
}
