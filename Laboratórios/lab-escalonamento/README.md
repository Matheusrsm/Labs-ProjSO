## Escalonador Probabilístico

1) É dado para cada ticket uma quantidade de tickets de acordo com sua prioridade. Tickets = 32 - prioridade

2) Os tickets serão sorteados usando funções nativas da linguagem. 

3) Cada ticket só poderá ser usado uma vez, caso ele seja sorteado mais de uma vez, seu sucessor numérico receberá a oportunidade até que um ticket não usado seja obtido. O mesmo acontecerá quando o processo sorteado não puder ser escalonado.

4) Será realizada uma nova distrubuião de tíckets sempre que todos os tíckets forem utilizados.


## Escalonador Determinístico

   
1) Definir uma prioridade inicial, em allocproc(), para todo processo que for criado.

2) Escolher o processo de maior prioridade

3) Após um processo ser executado sua prioridade inicial é atribuida novamente

4) Para não haver starvation, a cada 150 ciclos a prioridade dos processos diminui. E caso um processo seja interrompido, sua prioridade sera a metade do que era inicialmente
