/**
 * @file strs.h
 * @author Micael Dias, Hugo Carvalho, Rui Gonçalves
 * @date 8/1/2021
 * @brief Standardized strings
 */

#ifndef STRS_H
#define STRS_H

#include "colors.h"

// Globals

#define H_STRS_INVALID_IMPUT RED("[!] Input Inválido\n")
#define H_STRS_MALLOC_FAILED RED("[!] Não foi possível alocar espaço\n")
#define H_STRS_MISSING_CAPACITY RED("[!] Tamanho inicial não definido\n")
#define H_STRS_PARSE_ERROR RED("[!] Software não esta pronto para executar o parsing\n")
#define H_STRS_LOAD_FAILED RED("[!] Falha ao carregar o ficheiro")
#define H_STRS_LOAD_REPLACE RED("[!] Já existiam dados na tabela. Novos foram carregados\n")
#define H_STRS_SAVE_SUCCESS GREEN("Guardado com Sucesso\n")
#define H_STRS_SAVE_FILE_ERROR RED("[!] Não foi possível guardar o ficheiro")
#define H_STRS_PATH_MISSING RED("[!] A localização do ficheiro não foi especificada\n")

#define H_STRS_EDIT YELLOW("Linha a editar:")
#define H_STRS_DELETE YELLOW("Linha a eliminar:")
#define H_STRS_EMPTY_TABLE RED("Tabela Vazia\n")

// ISS
#define H_STRS_NEW_CRITERIA YELLOW("\nNovo critério: ")
#define H_STRS_CRITERIA_DUPLICATE RED("[!] Já existe um critério com esse nome. Abortar...\n")


#define H_STRS_MENU MAGENTA( \
"*******************************\n" \
"*         -|  MENU  |-        *\n" \
"*                             *\n" \
"* 1. Tabelas Retenção IRS     *\n" \
"* 2. Tabelas Segurança Social *\n" \
"* 3. Gestão de Funcionários   *\n" \
"* 4. Processar Salarios       *\n" \
"* 5. Relatórios               *\n" \
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
"* 0. Voltar ao menu anterior    *\n" \
"*                               *\n" \
"*********************************\n")

#define H_STRS_EMPLOYEES_MENU CYAN( \
"**************************************\n" \
"* -| Menu Gestão de Funcionários |-  *\n" \
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

#define H_STRS_REPORTS_MENU CYAN( \
"****************************************************\n" \
"*                  -| Relatórios |-                *\n" \
"*                                                  *\n" \
"* 1. Antiguidades dos funcionários                 *\n" \
"* 2. Percentagem de funcionários por estado civil  *\n" \
"* 3. Percentagem de funcinários que ganharam bonus *\n" \
"* 0. Voltar ao menu anterior                       *\n" \
"*                                                  *\n" \
"***************************************************\n")

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

#define H_STRS_PROC_TABLE_HEADER BLUE( \
"*********************************************************\n" \
"* [Linha] | Cod  | Dias      | Meios | Fins   | Faltas  *\n" \
"*         | Func | Completos | Dias  | Semana |         *\n" \
"*********************************************************\n")

#endif //STRS_H
