/*
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _STRS_H_
#define _STRS_H_

#include "colors.h"

#define H_STRS_INVALID_IMPUT "Input Inválido"
#define H_STRS_PROMPT "> "
#define H_STRS_PROMPT_NEW_LINE "\n> "

#define H_STRS_EDIT "Editar linha?"
#define H_STRS_DELETE "Apagar linha?"

#define H_STRS_MENU MAGENTA( \
"*******************************\n" \
"*         -|  MENU  |-        *\n" \
"*                             *\n" \
"* 1. Tabelas Retenção IRS     *\n" \
"* 2. Tabelas Segurança Social *\n" \
"* 9. Guardar                  *\n" \
"* 0. Sair                     *\n" \
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
"* -| Tabela I - NÃO CASADO |-                       *\n" \
"* 1. Visualizar                                     *\n" \
"* 2. Editar                                         *\n" \
"* 3. Adicionar                                      *\n" \
"* 4. Eliminar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela II - CASADO UNICO TITULAR |-            *\n" \
"* 5. Visualizar                                     *\n" \
"* 6. Editar                                         *\n" \
"* 7. Adicionar                                      *\n" \
"* 8. Eliminar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela III - CASADO DOIS TITULAR |-            *\n" \
"* 9.  Visualizar                                    *\n" \
"* 10. Editar                                        *\n" \
"* 11. Adicionar                                     *\n" \
"* 12. Eliminar                                      *\n" \
"*                                                   *\n" \
"* 0. Voltar ao menu anterior                        *\n" \
"*                                                   *\n" \
"*****************************************************\n")

#define H_STRS_SEG_SOCIAL_MENU MAGENTA( \
"**************************************\n" \
"* -| Menu Tabela Segurança Social |- *\n" \
"*                                    *\n" \
"* 1. Visualizar                      *\n" \
"* 2. Adicionar                       *\n" \
"* 3. Remover                         *\n" \
"* 4. Editar                          *\n" \
"* 0. Voltar ao menu anterior         *\n" \
"*                                    *\n" \
"**************************************\n")

#define H_STRS_IRS_TABLE_HEADER BLUE( \
"***********************************************************\n" \
"* Linha | Remuneração     | Numero de Dependentes         *\n" \
"*       | Mensal em €     | 0 | 1 | 2 | 3 | 4 | 5 ou mais *\n" \
"***********************************************************\n")

#endif //_STRS_H_
