# Trabalho Sistemas Operacionais TT304
Projeto desenvolvido para  a  disciplina  Sistemas  Operacionais, na Faculdade de Tecnologia da UNICAMP, sob a orientação do Prof. Dr. André Leon S. Gradvohl.
Após a criação da instância AWS solicitada no trabalho, o usuário deve instalar o compilador Gnu  Compiler  Collection  (GCC), o que pode ser feito através do comando:

sudo yum install gcc

Ao fazer o download do arquivo no formato .c contido neste repositório, o usuário deve fazer upload do mesmo na máquina virtual da AWS e posteriormente compilá-lo, gerando um programa executável.

Comando para compilação: gcc "nome_do_arquivo.c" -o "nome_do_arquivo_executável" -pthread

Note que é obrigatório o use do argumento -pthread, pois ele indica que o compilador deve usar a biblioteca pthread.
Com isso, basta executar o programa para testar a tarefa de programação.

Comando: ./nome_do_arquivo_executável

Obs: "nome_do_arquivo.c" foi definido na instância como "trabso.c" e "nome_do_arquivo_executável" como "trabso".
