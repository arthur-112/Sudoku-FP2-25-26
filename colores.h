#pragma once

// Otra idea de colores en C/C++: 
// 
// https://gist.github.com/Alfonzzoj/db207b89d56f24d9d0b17ff93e091be8
// 
//     cout << BLUE << BG_LGREEN << "This text is BLUE!     " << RESET << endl; // reset es lo que permite cambiar el color de fondo
//     cout << BLUE << "This text is BLUE!     "<< endl;

//===Color font code===/

// ANSI Escape codes
#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

// Colores RGB: Cualquier RGB color (Con valores en [0-255])	\x1B[38;2;R;G;Bm
// 38 para colores personalizados
#define ORANGE  "\x1b[38;2;255;128;0m"
#define ROSE    "\x1b[38;2;255;151;203m"
#define LBLUE   "\x1b[38;2;53;149;240m"
#define DBLUE   "\x1b[38;2;11;11;100m"
#define LGREEN  "\x1b[38;2;17;245;120m"
#define DGREEN  "\x1b[38;1;50;32;120m"
#define DRED    "\x1b[38;2;128;0;0m"
#define GRAY    "\x1b[38;2;176;174;174m"

// Cualquier color (con V en [0-255])	\x1B[38;5;Vm	\x1B[48;5;Vm
#define PROBANDO   "\x1b[38;5;100m"

// Al final de la instrucción para cambiar el color de fondo
#define RESET   "\x1b[0m"

//===Color background code===/

#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"

// Colores RGB: Cualquier RGB color (Con valores en [0-255])	\x1B[48;2;R;G;Bm
// 48 son para colores personalizados
#define BG_ORANGE  "\x1B[48;2;255;128;0m"
#define BG_ROSE    "\x1B[48;2;255;151;203m"
#define BG_LBLUE   "\x1B[48;2;53;149;240m"
#define BG_LGREEN  "\x1b[48;2;17;245;120m"
#define BG_GRAY    "\x1B[48;2;176;174;174m"

// Cualquier color (con V en [0-255])	\x1B[38;5;Vm	\x1B[48;5;Vm
#define BG_PROBANDO   "\x1b[48;5;100m"
