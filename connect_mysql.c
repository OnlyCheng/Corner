#include <stdio.h>
#include <mysql.h>

int main()
{
    printf("%s\n",mysql_get_client_info());

    MYSQL* sql = mysql_init(NULL);
    if(mysql_real_connect(sql,"127.0.0.1","root","xzzcjm1314","student",0,NULL,0) == 0)
    {
        printf("mysql connect err\n");
        exit(1);
    }
    
    const char* p = "insert into stu values(3,\"guai\")";
    mysql_query(sql,p);

    p = "select * from stu";
    mysql_query(sql,p);

    MYSQL_RES* result = mysql_store_result(sql);
    int row = mysql_num_rows(result);
    int col = mysql_num_fields(result);
    printf("row : %d ,col : %d\n",row,col); //ceshi
    MYSQL_FIELD* field  = mysql_fetch_fields(result);
    int i = 0;
    int j = 0;
    for(; i<col; i++)
        printf("%s\t",field[i].name);
    putchar('\n');
    MYSQL_ROW lines;
    for(i = 0; i<row; i++)
    {
        lines = mysql_fetch_row(result);//huo qu yi hang
        for(j=0; j<col; j++)
            printf("%s\t",lines[j]);
        printf("\n");
    }
    mysql_close(sql);
    free(result);

    return 0;
}
