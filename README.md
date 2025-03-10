Please, put your code in order (norminette);

Adicionei o exit_status na parte da execução, \
mas creio que o valor ainda não está a ser exportado no "?"

Run more tests

"echo argument > file" está a dar bug porque ele não pára de dup(fd, STDOUT_FILEONE);
O problema resolvido se for feito fork() e terminar devidamente o child, mas ainda \
não fiz, tenho preguiça (nem sei mesmo se vai resultar hahaha)

E adicionei o file "NORMINETTE CHECK" para distinguir o que já está fixe.

Luanda, aos 06 de Março de 2025

Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon)
