/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _STRS_H_
#define _STRS_H_

#include "colors.h"

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
"* 2. Adicionar Linha                                *\n" \
"* 3. Editar Linha                                   *\n" \
"* 4. Eliminar Linha                                 *\n" \
"*                                                   *\n" \
"* 5. Visualizar Tabela II - CASADO UNICO TITULAR    *\n" \
"* 6. Adicionar Linha                                *\n" \
"* 7. Editar Linha                                   *\n" \
"* 8. Eliminar Linha                                 *\n" \
"*                                                   *\n" \
"* 9. Visualizar Tabela III - CASADO DOIS TITULAR    *\n" \
"* 10. Adicionar Linha                               *\n" \
"* 11. Editar Linha                                  *\n" \
"* 12. Eliminar Linha                                *\n" \
"*                                                   *\n" \
"* 0. Voltar ao menu anterior                        *\n" \
"*                                                   *\n" \
"*****************************************************\n")

#define H_STRS_SAVE_MENU RED( \
"******************\n" \
"*   SAVE (Y/n)   *\n" \
"******************\n")

#define H_STRS_IRS_TABLE_HEADER BLUE( \
"***************************************************\n" \
"* Remuneração     | Numero de Dependentes         *\n" \
"* Mensal em Euros | 0 | 1 | 2 | 3 | 4 | 5 ou mais *\n" \
"***************************************************")

#define H_STRS_IRS_TABLE_EDIT(string) RED( \
"[!] Editar " string "\n" \
"> Linha?\n")


#endif //_STRS_H_
