/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _STRS_H_
#define _STRS_H_

#include "colors.h"

#define H_STRS_IRS_TEMPLATE_STRING "%s;%.2fEUR;%.1f%%;%.1f%%;%.1f%%;%.1f%%;%.1f%%;%.1f%%;\n"

#define H_STRS_MENU MAGENTA( \
"\n*******************************\n" \
"*        -|  MENU  |-         *\n" \
"*                             *\n" \
"*   1. Tabelas Retenção IRS   *\n" \
"*   9. Guardar                *\n" \
"*   0. Sair                   *\n" \
"*                             *\n" \
"*******************************\n")

#define H_STRS_IRS_MENU MAGENTA( \
"*****************************************************\n" \
"*         -| Menu Tabelas de Retenção IRS |-        *\n" \
"*                                                   *\n" \
"*  TABELAS DE RETENÇÃO NA FONTE PARA O CONTINENTE   *\n" \
"*                                                   *\n" \
"*                TRABALHO DEPENDENTE                *\n" \
"*                                                   *\n" \
"* 1. Visualizar Tabela I - NÃO CASADO               *\n" \
"* 2. Editar Linha                                   *\n" \
"*                                                   *\n" \
"* 3. Visualizar Tabela II - CASADO UNICO TITULAR    *\n" \
"* 4. Editar Linha                                   *\n" \
"*                                                   *\n" \
"* 5. Visualizar Tabela III - CASADO DOIS TITULAR    *\n" \
"* 6. Editar Linha                                   *\n" \
"*                                                   *\n" \
"* 0. Voltar ao menu anterior                        *\n" \
"*                                                   *\n" \
"*****************************************************\n")

#define H_STRS_IRS_TABLE_HEADER BLUE( \
"***************************************************\n" \
"* Remuneração     | Numero de Dependentes         *\n" \
"* Mensal em Euros | 0 | 1 | 2 | 3 | 4 | 5 ou mais *\n" \
"***************************************************")

#define H_STRS_IRS_TABLE_EDIT(string) RED( \
"[!] Editar " string "\n" \
"> Linha?\n")

#endif //_STRS_H_
