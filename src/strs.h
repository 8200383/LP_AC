/**
 * @file strs.h
 * @author Micael Dias, Hugo Carvalho, Rui Gonçalves
 * @date 8/1/2021
 * @brief Standardized strings
 */

#ifndef STRS_H
#define STRS_H

#include "colors.h"

#define H_STRS_INVALID_IMPUT RED("Input Inválido\n")

#define H_STRS_EDIT YELLOW("Editar linha?")
#define H_STRS_DELETE YELLOW("Apagar linha?")
#define H_STRS_EMPTY_TABLE RED("Tabela Vazia.\n")
#define H_STRS_SAVE_SUCCESS GREEN("Guardado com Sucesso.\n")

#define H_STRS_CRITERIA_DUPLICATE RED("Já existe um critério com esse nome.\n")

#define H_STRS_MENU MAGENTA( \
"*******************************\n" \
"*         -|  MENU  |-        *\n" \
"*                             *\n" \
"* 1. Tabelas Retenção IRS     *\n" \
"* 2. Tabelas Segurança Social *\n" \
"* 3. Gestão de Funcionários   *\n" \
"* 4. Processar Salarios       *\n" \
"* 9. Guardar Tudo             *\n" \
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
"*  1. Carregar Tabela                               *\n" \
"*  2. Visualizar                                    *\n" \
"*  3. Editar                                        *\n" \
"*  4. Adicionar                                     *\n" \
"*  5. Eliminar                                      *\n" \
"*  6. Guardar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela II - CASADO UNICO TITULAR |-            *\n" \
"*  7. Carregar Tabela                               *\n" \
"*  8. Visualizar                                    *\n" \
"*  9. Editar                                        *\n" \
"* 10. Adicionar                                     *\n" \
"* 11. Eliminar                                      *\n" \
"* 12. Guardar                                       *\n" \
"*                                                   *\n" \
"* -| Tabela III - CASADO DOIS TITULAR |-            *\n" \
"* 13. Carregar Tabela                               *\n" \
"* 14. Visualizar                                    *\n" \
"* 15. Editar                                        *\n" \
"* 16. Adicionar                                     *\n" \
"* 17. Eliminar                                      *\n" \
"* 18. Guardar                                       *\n" \
"*                                                   *\n" \
"* 0. Voltar ao menu anterior                        *\n" \
"*                                                   *\n" \
"*****************************************************\n")

#define H_STRS_SEG_SOCIAL_MENU MAGENTA( \
"**************************************\n" \
"* -| Menu Tabela Segurança Social |- *\n" \
"*                                    *\n" \
"* 1. Carregar Tabela                 *\n" \
"* 2. Visualizar                      *\n" \
"* 3. Adicionar                       *\n" \
"* 4. Remover                         *\n" \
"* 5. Editar                          *\n" \
"* 6. Guardar                         *\n" \
"* 0. Voltar ao menu anterior         *\n" \
"*                                    *\n" \
"**************************************\n")

#define H_STRS_PROC MAGENTA( \
"*********************************\n" \
"*  -| Processamento Salarios |- *\n" \
"*                               *\n" \
"*  1. Criar mês                 *\n" \
"*  2. Visualizar                *\n" \
"*  3. Adicionar detalhes        *\n" \
"*  4. Editar detalhes           *\n" \
"*  5. Eliminar detalhes         *\n" \
"*  6. Processar mês             *\n" \
"*  7. Exportar mês para CSV     *\n" \
"*  8. Guardar                   *\n" \
"*  9. Importar mês              *\n" \
"* 10. Desfazer todas alterações *\n" \
"* 0. Sair                       *\n" \
"*                               *\n" \
"*********************************\n")

#define H_STRS_IRS_TABLE_HEADER BLUE( \
"*************************************************************\n" \
"* [Linha] | Remuneração     | Numero de Dependentes         *\n" \
"*         | Mensal em €     | 0 | 1 | 2 | 3 | 4 | 5 ou mais *\n" \
"*************************************************************\n")

#define H_STRS_SS_TABLE_HEADER BLUE( \
"*************************************************\n" \
"* [Linha] | Critério | Percentagens de Retenção *\n" \
"*         |          | Empregador | Empregado   *\n" \
"*************************************************\n")

#define H_STRS_EMPLOYEES_TABLE_HEADER GREEN( \
"*********************************************************************************************************************************************************\n" \
"* [Linha] | Cod | Primeiro | Último   | Tlf. | Nº Dependentes | Cargo | Estado | Data       | Data    | Data  | Valor Base | Subsídio    | Nº Titulares *\n" \
"*         |     | Nome     | Nome     |      |                |       | Cívil  | Nascimento | Entrada | Saída | Rendimento | Alimentação |              *\n" \
"*********************************************************************************************************************************************************\n")

#define H_STRS_EMPLOYEES_MENU CYAN ( \
"**************************************\n" \
"* -| Menu Gestão de Funcionários |-  *\n" \
"*                                    *\n" \
"* 1. Visualizar                      *\n" \
"* 2. Adicionar                       *\n" \
"* 3. Remover                         *\n" \
"* 4. Editar                          *\n" \
"* 0. Voltar ao menu anterior         *\n" \
"*                                    *\n" \
"************************************** \n")

#define H_STRS_PROC_TABLE_HEADER BLUE( \
"*********************************************************\n" \
"* [Linha] | Cod  | Dias      | Meios | Fins   | Faltas  *\n" \
"*         | Func | Completos | Dias  | Semana |         *\n" \
"*********************************************************\n")

#endif //STRS_H
