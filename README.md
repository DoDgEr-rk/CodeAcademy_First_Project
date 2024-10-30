Да се напише програма, която проверява в директория (входен параметър на програмата) за наличието на файл с име IMPORT_INVOICES_YYYYMMDD_HH24MISS.txt , където YYYYMMDD_HH24MISS е дата, час, минути и секунди, например 20230401_152022.
Програмата проверява, че съдържанието на файла е следното :
На първи ред има едно число X, което е броя редове във файла (например X=20). Следват X-2 реда с еднакъв формат, на всеки ред има следните данни – Име на клиент, номер на фактура, дата, валута, сума. Последният ред във файла е една сума.
Трябва да се провери, дали форматът на данните е правилен. 
Първи ред – число. Да се провери, че това е броя редове във файла.
......................................................................
Всички без последен ред – разделени с символ ; данни:  Име – само букви; номер на фактура – букви и цифри; дата във формат DDMMYYYY; Валута – една от стойностите BGN, USD, EUR, RSD, TND; сума на фактурата– число с десетична запетая (символ . ).
Последен ред – число с десетична запетая. Да се провери, че числото на последния ред е равно на сумата на фактурите от всички редове. 
Пример за верен файл:
6
IRINA;FN12345;03012023;BGN;345.78
NENO;FN23456;20122022;USD;35
IVELINA;FN23334;28122022;BGN;500
MILENA;FN00098;04012023;EUR;75.25
956.03

......................................................................
Ако форматът на файла е коректен се преименува на IMPORT_INVOICES_YYYYMMDD_HH24MISS.OK и се отваря нов файл с име INVOICES_ORDERED_YYYYMMDD_HH24MISS.txt, където линиите се принтират подредени по сумата на фактурата от най-малката на първа линия до най-голямата на последна линия Ако сумата е еднаква да се сортира с приоритет: Име, номер на фактура, датата в зададения формат(DDMMYYYY).
Ако има грешка във формата, файлът се преименува на IMPORT_INVOICES_YYYYMMDD_HH24MISS.KO и се изписва на конзолата каква е грешката.
