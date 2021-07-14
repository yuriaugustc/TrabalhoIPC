#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define setbuff setbuf(stdin, NULL)
#define cls system("cls")

struct Aluno{
    char nomeCompleto[100];
    char matricula[12];
    char email[100];
    char curso[100];
    char materias[5][100];
    char motivo[1000];
    int cadastro;
    int trancamento;
    int auxilio;
    int solicitacao;
    int estagio;
    char empresa[50];
    char data[10];
    char hora[10];
};

void arquivo(struct Aluno matricula[], int *contador){
    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "a");

    fprintf(fcadastro,"Matrícula: %s\n", matricula[*contador].matricula);
    fprintf(fcadastro,"Nome: %s\n", matricula[*contador].nomeCompleto);
    fprintf(fcadastro,"Email: %s\n", matricula[*contador].email);
    fprintf(fcadastro, "------------------------------------------------\n");
    fclose(fcadastro);

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[*contador].matricula);
    fprintf(flog,"Ação: Cadastro\n");
    if(matricula[*contador].cadastro == 1){
         fprintf(flog,"Deferido: Sim\n");  
    }else{
        fprintf(flog,"Deferido: Nao\n");
    }
    fprintf(flog,"Data: %s\n", _strdate(matricula[*contador].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[*contador].hora));
    fprintf(flog,"-------------------------------------------\n");
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);
}//arquivo

void cadastro(struct Aluno matricula[], int *contador){
    int i = *contador;
    int aux, verifica = 0;
    char matr[12], mat[12], nome[100], email[100], ignorar[100], lixo[100];
    matricula[i].cadastro = 0;
    
    cls;
    printf("\n*** Cadastro ***\n");
    printf("Digite seu nome completo: ");
    setbuff;
    scanf("%[^\n]s",matricula[i].nomeCompleto);
    printf("\nNOTA: A sua matrícula deve possuir 11 caracteres!");
    printf("\nDigite sua matricula: ");
    scanf("%s",matricula[i].matricula);
    while(strlen(matricula[i].matricula)!=11){
        printf("\nA sua matrícula deve possuir 11 caracteres!");
        printf("\nDigite sua matricula: ");
        scanf("%s",matricula[i].matricula);
        }
    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matricula[i].matricula)){ 
            verifica = 1;
            break;}
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    fclose(fcadastro);
    if(verifica == 1){
        printf("\nEsta matrícula já está cadastrada!\n");
        printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
        getch();
        return;
    }
    printf("\nDigite seu email: ");
    scanf("%s",matricula[i].email);
    printf("\nCadastro realizado com sucesso!");
    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    matricula[i].cadastro = 1;
    arquivo(matricula, contador);
    (*contador)++;
    getch();
}//cadastro

void trancamento(struct Aluno matricula[], int *contador){
    int i = 0, aux;
    char opcao;
    char matr[12], mat[12], nome[100], email[100], ignorar[100], lixo[100];
    char motivo[1000];

    cls;
    printf("\n\n*** icitacaoicitação de Trancamento de curso ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    fclose(fcadastro);
    if(aux == EOF){
        printf("\nVocê não possui uma matrícula cadastrada em nosso sistema para realizar trancamento!\n");
        printf("\nDeseja realizar um cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
        printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
        getch();
        }
        return;
    }
    if(matricula[i].trancamento == 1){
        printf("\nSua matrícula já está trancada, deseja destrancar seu curso (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            matricula[i].trancamento = 0;
            printf("\nMatrícula destrancada com sucesso!\n");
        }
        printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
        getch();
        return;
    }
    printf("\nInforme o motivo de trancamento de curso: \n");
    setbuff;
    scanf("%[^\n]s", matricula[i].motivo);
        printf("\n  Todas solicitações deferidas serão canceladas e você terá de solicitar novamente ");
        printf("quando destrancar seu curso;");
    printf("\nVocê tem certeza que deseja trancar o curso (s/n)? ");
    scanf(" %c", &opcao);
    if(opcao == 's' || opcao == 'S'){
        matricula[i].trancamento = 1;
        matricula[i].estagio = 0;
        matricula[i].empresa[0] = '\0';
        matricula[i].auxilio = 0;
        matricula[i].materias[1][0] = '\0';
        printf("\nMatrícula trancada com sucesso!\n");
    }

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Trancamento de Curso\n");
    if(matricula[i].trancamento == 1){
         fprintf(flog,"Deferido: Sim\n");  
    }else{
        fprintf(flog,"Deferido: Nao\n");
    }
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
}//trancamento

void mat_curso(struct Aluno matricula[], int *contador){
    int num_materias, i = 0, aux = 0, cont = 0;
    char opcao;
    char texto[100], matr[12], mat[12], nome[100], email[100], ignorar[100], lixo[100];
    
    cls;
    printf("\n\n*** Solicitação de Matrícula no Curso ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    fclose(fcadastro);
    if(aux == EOF){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
    return;
    }
    for(i = 0; i < 30; i++){
        if(!strcmp(matricula[i].matricula, matr))
            break;
    } 
    if(matricula[i].trancamento == 1){ 
        printf("\nSua matrícula está trancada no curso.");
        printf("\nPara solicitação de matrícula no curso, sua matrícula deve estar ativa no curso.");
        printf("\nDeseja realizar destrancamento do curso (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            trancamento(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
        return;
    }
    printf("Deseja verificar as matérias de cada período antes de iniciar a solicitação (s/n)? ");
    setbuff;
    scanf(" %c", &opcao);
    if(opcao == 's' || opcao == 'S'){
        FILE *fmat;
        fmat = fopen("materias.txt", "r");
        printf("A seguir, será apresentado as matérias de cada período, aguarde até o fim da impressão.\n");
        Sleep(4000);
        fgets(texto, 100, fmat);
        printf("%s", texto); 
        while(1){
            void *retorno = fgets(texto, 100, fmat);
            printf("%s", texto);
            if(retorno == NULL) break;
            cont++;
            if(cont == 7){
                Sleep(2000);
                cont = 0;
            }
        }
        fclose(fmat);
    }
    printf("NOTA: A compatibilidade de horários entre as matérias é de total responsabilidade do estudante.\n");
    Sleep(2000);
    printf("\nDigite quantas matérias você deseja se matricular: ");
    scanf("%d", &num_materias);
    FILE *fsol;
    fsol = fopen("matricula.txt", "a");
    fprintf(fsol, "Matrícula: %s\n", matricula[i].matricula);
    for(i = 0; i < num_materias; i++){
        printf("\nDigite a(s) materia(s) que deseja se matricular: ");
        setbuff;
        scanf("%[^\n]s", matricula[i].materias[i]);
        fprintf(fsol,"Matéria(s) matrículada(s): %s\n", matricula[i].materias[i]);
    }
    fprintf(fsol, "-------------------------------------------\n");
    fclose(fsol);

    matricula[i].solicitacao = 1;

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Solicitação de Matrícula\n");
    if(matricula[i].solicitacao == 1){
         fprintf(flog,"Deferido: Sim\n");  
    }else{
        fprintf(flog,"Deferido: Nao\n");
    }
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nSolicitação realizada com sucesso!\n");
    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
}//mat_curso

void estagio(struct Aluno matricula[], int *contador){
    int i = 0, aux;
    int periodo;
    char opcao;
    char matr[12], mat[12], nome[100], email[100], ignorar[100], lixo[100];;

    cls;
    printf("\n\n*** Solicitação de Estágio ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    for(i = 0; i < 30; i++){
        if(!strcmp(matricula[i].matricula, matr))
            break;
    }
    fclose(fcadastro); 
    if(aux == EOF){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
    return;
    }
    if(matricula[i].trancamento == 1){ 
        printf("\nSua matrícula está trancada no curso.");
        printf("\nPara solicitação de estágio, sua matrícula deve estar ativa no curso.");
        printf("\nDeseja realizar destrancamento do curso (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            trancamento(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
        return;
    }
    printf("Para prosseguir, digite seu periodo: ");
    setbuff;
    scanf("%d", &periodo);
    if(periodo <= 2){
        printf("Você não pode solicitar estágio antes do 3° período.");        
    }
    else{
        printf("Digite a empresa que você deseja realizar seu estágio: ");
        setbuff;
        scanf(" %[^\n]s", matricula[i].empresa);
        printf("Certo, para confirmar se você possui os requisitos para solicitar um estágio, envie por favor os documentos ");//quebra de texto para nao ficar extenso
        printf("necessários listados no Portal de Graduação da UFU (PROGRAD) e envie para o setor de estágios (estagio@prograd.ufu.br).\n");
        printf("Após verificação, enviaremos um email com a próxima etapa para dar continuidade em sua solicitação.\n");
        matricula[i].estagio = 1;
    }

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Solicitação de Estágio\n");
    if(matricula[i].estagio == 1){
         fprintf(flog,"Deferido: Sim\n");  
    }else{
        fprintf(flog,"Deferido: Nao\n");
    }
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
}//estagio

void auxilio(struct Aluno matricula[], int *contador){
    float salario;
    int qtd, i;
    float percpt = 0, aux = 0, aux1 = 0;
    char opcao;
    char matr[12], mat[12], nome[100], email[100], ignorar[100], lixo[100];

    cls;
    printf("\n\n*** Solicitação de Auxílio Ensino Remoto ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    for(i = 0; i < 30; i++){
        if(!strcmp(matricula[i].matricula, matr))
            break;
    }
    fclose(fcadastro);    
    if(aux == EOF){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
    return;
    }
    if(matricula[i].trancamento == 1){ 
        printf("\nSua matrícula está trancada no curso.");
        printf("\nPara solicitação de auxílio, sua matrícula deve estar ativa no curso.");
        printf("\nDeseja realizar destrancamento do curso (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            trancamento(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
        return;
    }
    printf("\nPara solicitação de auxílio, informe na respectiva ordem, a quantidade de pessoas e renda de cada.\n");
    printf("Quantidade de pessoas: ");
    scanf("%d", &qtd);
    float pessoas[qtd];
    for(i = 0; i< qtd; i++){
        printf("Digite o salário: ");
        scanf("%f", &aux);
        pessoas[i] = aux;
        aux1 = aux + aux1;
        }
        percpt = aux1/qtd;
        if(percpt > 1497){
            printf("\nVocê não pode receber auxílio com renda per capita acima de 1,5 salario mínimo per capita.\n");
    }
    else{
        printf("\nPara prosseguir, envie os documentos necessários para validação da solicitação para o email correspondente na página ");
        printf("de solicitação do PROGRAD.\n Em caso de confirmação, será enviado em seu e-mail as próximas etapas para solicitação do auxílio;\n");
        matricula[i].auxilio = 1;
    }

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Solicitação de Auxílio Ensino Remoto\n");
    if(matricula[i].auxilio == 1){
         fprintf(flog,"Deferido: Sim\n");  
    }else{
        fprintf(flog,"Deferido: Nao\n");
    }
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
}//auxilio

void reescreve(struct Aluno matricula[], int *contador){
    int i = 0;
    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "w");
    fprintf(fcadastro,"------------ Lista de Cadastro -----------------\n");
    fprintf(fcadastro,"------------------------------------------------\n");
    do{
    fprintf(fcadastro,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(fcadastro,"Nome: %s\n", matricula[i].nomeCompleto);
    fprintf(fcadastro,"Email: %s\n", matricula[i].email);
    fprintf(fcadastro, "------------------------------------------------\n");
    i++;
    }while(i != (*contador));
    fclose(fcadastro);
}//reescreve

void atualiza_cad(struct Aluno matricula[], int *contador){
    int i, aux, op;
    char matr[12], mat[12], ignorar[100], lixo[100], nome[100], email[100];
    char opcao;

    cls;
    printf("\n\n*** Atualização de Cadastro ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r+");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    for(i = 0; i < 30; i++){
        if(!strcmp(matricula[i].matricula, matr))
            break;
    }
    if(aux == EOF){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
    return;
    }
    
    printf("\nQual dos seus dados você deseja atualizar? \n");
    printf("1 - Nome\n");
    printf("2 - Matrícula\n");
    printf("3 - Email\n");
    printf("Digite a opção desejada: ");
    setbuff;
    scanf("%d", &op);
    if(op == 1){
        printf("Digite o novo nome: ");
        scanf(" %[^\n]s", matricula[i].nomeCompleto);
        reescreve(matricula, contador);
        printf("Nome alterado com sucesso!\n");
    }
    if(op == 2){
        printf("Digite a nova matrícula: ");
        scanf(" %[^\n]s", matricula[i].matricula);
        while(strlen(matricula[i].matricula)!=11){
            printf("A matrícula deve possuir 11 caracteres!\n"); 
            printf("Digite a nova matrícula: ");
            scanf("%s", mat);
            }
        reescreve(matricula, contador);
        printf("Matrícula alterada com sucesso!\n");
    }
    if(op == 3){
        printf("Digite o novo email: ");
        scanf(" %s", matricula[i].email);
        reescreve(matricula, contador);
        printf("Email alterado com sucesso!\n");
    }
    if(op == 4){
        printf("Digite o novo nome: ");
        scanf(" %[^\n]s", matricula[i].nomeCompleto);
        printf("Digite o novo nome: ");
        scanf(" %s", matricula[i].matricula);
        printf("Digite o novo email: ");
        scanf(" %s", matricula[i].email);
        reescreve(matricula, contador);
        printf("Cadastro alterado com sucesso!\n");
    }

    fclose(fcadastro);

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Atualização de Cadastro\n");
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
    setbuff;
}//atualiza_cad

void consulta_cad(struct Aluno matricula[], int *contador){
    char ignorar[100], lixo[100], nome[100], email[100];
    int aux, i;
    char matr[12], mat[12], data[10], hora[10];
    char opcao;
    
    system("cls");
    printf("\n\n*** Consulta de Cadastro ***\n");

    FILE *fcadastro;
    fcadastro = fopen("cadastro.txt", "r");
    fgets(lixo, 100, fcadastro);
    fgets(lixo, 100, fcadastro);
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
    while(1){
        aux = fscanf(fcadastro, "%s %s\n", ignorar, mat);
        if(!strcmp(mat, matr)) break;
        if(aux == EOF) break;
        fgets(nome, 100, fcadastro);
        fgets(email, 100, fcadastro);
        fgets(lixo, 100, fcadastro);
    }
    for(i = 0; i < 30; i++){
        if(!strcmp(matricula[i].matricula, matr))
            break;
    }
    if(aux == EOF){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
        return;
    }
    printf("\nEste é seu cadastro:\n");
    fgets(nome, 100, fcadastro);
    printf("\n%s", nome);
    printf("%s %s\n", ignorar, mat);
    fgets(email, 100, fcadastro);
    printf("%s", email);
    fclose(fcadastro);

    printf("Matrícula trancada? ");
    if(matricula[i].trancamento == 1){ 
        printf("Sim");}
    else{ 
        printf("Não");}
    printf("\nRealizando estágio? ");
    if(matricula[i].estagio == 1){ 
        printf("Sim\n");
        printf("Empresa: %s\n", matricula[i].empresa);}
    else{ 
        printf("Não\n");}

    printf("\n\nDeseja realizar atualização de cadastro (s/n)? ");
    setbuff;
    scanf(" %c", &opcao);
    if(opcao == 's' || opcao == 'S'){
        atualiza_cad(matricula, contador);
        printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
        getch();
        return;
    }
    printf("\n\nDeseja realizar uma nova consulta (s/n)? ");
    setbuff;
    scanf(" %c", &opcao);
    if(opcao == 's' || opcao == 'S'){
        consulta_cad(matricula, contador);
    }

    FILE *flog;
    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matr);
    fprintf(flog,"Ação: Consulta de Cadastro\n");
    fprintf(flog,"Data: %s\n", _strdate(data));
    fprintf(flog,"Hora: %s\n", _strtime(hora));
    fprintf(flog,"-------------------------------------------\n");
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);
    
    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();
}//consulta_cad

void consulta_sol(struct Aluno matricula[], int *contador){
    int i = 0, aux, cont;
    char opcao;
    char matr[12], mat[12];
    char lixo[100], ignorar[100], acao[100], deferido[100];
    FILE *flog;
    flog = fopen("log.txt", "r");
    fgets(lixo, 100, flog);
    fgets(lixo, 100, flog);
    cls;
    printf("\n\n*** Consultar Solicitações ***\n"); 
    setbuff;
    printf("\nDigite sua matrícula: ");
    scanf("%s", matr);
        printf("\nEstas são as solitações feitas pelo seu usuário:\n");
    while(1){
        aux = fscanf(flog, "%s %s\n", ignorar, mat);
        fgets(acao, 100, flog);
        fgets(deferido, 100, flog);
        fgets(lixo, 100, flog);
        fgets(lixo, 100, flog);
        fgets(lixo, 100, flog);
        if(aux == EOF) break;
        if(!strcmp(mat, matr)){
            printf("%s", acao);
            printf("%s", deferido);
            cont++;
        }
    }
    if(aux == EOF && cont == 0){
        printf("\nSua matrícula não possui cadastro em nosso sistema, deseja realizar o cadastro (s/n)? ");
        setbuff;
        scanf(" %c", &opcao);
        if(opcao == 's' || opcao == 'S'){
            cadastro(matricula, contador);
        }
        else{
            printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
            getch();
        }
        return;
    }

    flog = fopen("log.txt", "a");
    fprintf(flog,"Matrícula: %s\n", matricula[i].matricula);
    fprintf(flog,"Ação: Consulta de Solicitações Feitas Pelo Usuário\n");
    fprintf(flog,"Data: %s\n", _strdate(matricula[i].data));
    fprintf(flog,"Hora: %s\n", _strtime(matricula[i].hora));
    fprintf(flog,"-------------------------------------------\n");
    fprintf(flog,"-------------------------------------------\n");
    fclose(flog);

    printf("\nPressione qualquer tecla para retornar ao menu principal.\n");
    getch();

}//consulta_sol

void menu(){
    int opcao, contador = 0;
    struct Aluno P[30];

    while(1){
        printf("\nBem vindo ao Sistema de Controle de Deferimento de Solicitações\n");
        printf("\n1- Cadastro ");
        printf("\n2- Trancamento de curso ");
        printf("\n3- Matrícula no Curso ");
        printf("\n4- Solicitação de Estágio ");
        printf("\n5- Auxilio Ensino Remoto ");
        printf("\n6- Consultar cadastro ");
        printf("\n7- Atualizar cadastro ");
        printf("\n8- Consultar Solicitações ");
        printf("\n9- Sair ");
        printf("\nDigite opção: ");
        scanf("%d", &opcao);

        if(opcao == 1) cadastro(P, &contador);
        if(opcao == 2) trancamento(P, &contador);
        if(opcao == 3) mat_curso(P, &contador);
        if(opcao == 4) estagio(P, &contador);
        if(opcao == 5) auxilio(P, &contador);
        if(opcao == 6) consulta_cad(P, &contador);
        if(opcao == 7) atualiza_cad(P, &contador);
        if(opcao == 8) consulta_sol(P, &contador);       
        if(opcao == 9) return;        
        }//while
}//menu

int main(){
    menu();
}//main