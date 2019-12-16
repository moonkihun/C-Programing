#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 500
typedef struct postfix {
    double n;    //연산자, 숫자
    short set;  //연산자 = 0, 숫자 = 1
}Postfix;

int correct_string(char *); //operator숫자를 리턴해주고 에러체크
void cut(char *,char *,char *,char *); //소수점을 중심으로 서로 나눠주는 함수
int ChangePostfix(Postfix *nums, Postfix *num, int cnt);//Postfix로 바꿔주는 함수
void swap(char *,char *); //p1,p2를 서로 바꿔주는 함수
void multiply(char *,char *); //곱셈함수
void plus(char *,char *); //덧셈함수
void minus(char *,char *); //뺄셈함수
int compare(char *,char *); //스트링 비교함수
int in(char *); //입력받아 넘겨주는 함수
void remove_space(char *); //공백문자 제거함수
int cal(char *); //계산함수
void division(char *,char *); //나눗셈 함수
void change(char *); //문자를 거꾸로 바꿔주는 함수
int check_oper(char *); //oprator를 체크하는 함수
int check_zero(char *); //스트링이 0인지 컴사하는 함수
int check_value(char *,char *); //스트링을 비교하는 함수
int size;
int main()
{
    char *input;
    printf("$calculator\n");
    printf("start ...\n");
 
    in(input)!=0;
    return 0;
}


// 문자열이 모두 0 인지 검사하기
int check_zero(char *s){
    int i;
    for(i=0;i<50 && i<strlen(s);i++)
        if(s[i] != '0')
            return 1;
        return 0;
}
int check_value(char *p1,char *p2)
{
    if(strlen(p1)<strlen(p2))
        return 1;
    if((strlen(p1) == strlen(p2)) && (strcmp(p1,p2) == -1)){
        return 1;
    }
    else
        return 0;
}
int in(char *input)
{
    int flag=1;
     input=(char *)malloc(sizeof(char)*MAX);
       FILE *fpp;
       FILE *fps;
       fps=fopen("input","r");
       if(fps==NULL){
          printf("실패\n");
        return 1;}
   // size = lseek(fps, 0, SEEK_END);
//	input = malloc(size + 1);
    //fgets(input,size+1,fps);
       fgets(input,MAX,fps);
    fclose(fps);
       if(input[strlen(input)-1]=='\n')
           input[strlen(input)-1]='\0';
       //end or END 문자열이면 프로그램 종료
       if(compare(input,"end")==0 || compare(input,"END")==0)
           return 0;
       remove_space(input);// ' ' 공백문자 제거
       if(correct_string(input) == 0 ){ // 올바른 문자인지 검사
           printf("error!!\n");
           return 1;
       }
       //calculation
       while(correct_string(input) != 1){ //operator가 없을 때까지 검사
           if(cal(input) == -1){ //입력된것이 에러가 있을경우
               printf("input error!!\n");
               flag=2; // 계산값을 출력 안하기 위해서
               break;
           }
       }
       // printf correct answer
       if(flag ==1)
           printf("= %s\n",input);
       free(input);
       return 1;
}
int compare(char *s1,char *s2){//스트링 비교
    if(strcmp(s1,s2)==0 && strlen(s1) == strlen(s2))//strcmp는 endd 와 end를 구별 못함.
        return 0;
    return 1;
}
int correct_string(char *s1){ //올바른 문자 검사(에러면 리턴 0),operator수를 리턴
    int i,flag=1;
    
    if(s1[0] == '\0')
        return 0;
    else if(s1[0] == '-') // 0번지 배열에 -(음수)일경우 operator가 아니게 함..
        flag--;
    for(i=0; i<strlen(s1);i++){
        if(s1[i] >='0' && s1[i] <='9') ; // 숫자 인지 검사
        else if(s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')
            flag++; // operator검사
        else if(s1[i] == '.'||s1[i]=='('||s1[i]==')') ; // ( ) . 검사
        else return 0;
    }
    return flag;
}
void remove_space(char *s){ // ' ' 공백문자 제거
    int i,j;
    for(i=0,j=0;j<strlen(s);j++,i++){
        while(s[j]==' ')
            j++;
        s[i]=s[j];
    }
    s[i]='\0';
}
void change(char *s){ // 문자를 거꾸로 바꿔줌
    char s1[MAX]={0};
    int i;
    for(i=0;i<strlen(s);i++)
        s1[i] = s[strlen(s)-i-1];
    s1[i] ='\0';
    strcpy(s,s1);
}
// p1과 p2의 소수점이전값과 이후의 값을 저장함.
void cut(char *p1,char *p2,char *p1_p,char *p2_p){
    int i;
    for(i=0;i<strlen(p1) && p1[i] !='.';i++);
    strcpy(p1_p,p1+i+1);
    p1[i]='\0';
    
    for(i=0;i<strlen(p2) && p2[i] !='.';i++);
    strcpy(p2_p,p2+i+1);
    p2[i]='\0';
}
void swap(char *p1,char *p2){// p1과 p2 자리 바꿈
    char tmp[MAX];
    strcpy(tmp,p1);
    strcpy(p1,p2);
    strcpy(p2,tmp);
}
int cal(char *s){ // 어떤 계산이 필요한지 1차적으로 제어하는 함수
    char data[MAX]={0},data_after[MAX]={0},p1[MAX]={0},p2[MAX]={0};
    int i,j,k,x;// point : i(left) , j(right),k(operator)
    for(j=0;j<strlen(s) && s[j] !=')';j++) ; // ')' 찾기
    if(s[j] == ')' ){// ')'찾음
        for(x=0,i=j-1;i>=0 && s[i] !='(';i--,x++)
            data[x] = s[i];
        data[x] = '\0';
        change(data);
        if(s[i] !='(') // '('못 찾음
	
            return -1; // error return
        strcpy(data_after,s+j+1);// ')'뒤에값 저장
        while(correct_string(data) != 1) // 연산자가 없을때까지
            cal(data);
        
        strcpy(s+i,data); // data연산후 의 값을 s배열에 넣어줌
        strcat(s,data_after); // s배열에 전에 )뒤에 값을 넣어줌
    }
    else {
        for(k=0; k<strlen(s) && s[k] !='*' && s[k] !='/';k++);
        
        if(s[k] == '*' || s[k] == '/'){
            //p1찾기
            for(x=0,i=k-1; i>=0 && s[i] !='+' && s[i] !='-'; i--,x++)
                p1[x] = s[i];
            p1[x] = '\0';
            change(p1);
            //p2찾기
            for(x=0,j=k+1; (j == k+1)|| (j<strlen(s) && s[j] !='+' && s[j] !='-' && s[j] !='*' && s[j] !='/');
            j++,x++)
                p2[x] = s[j];
            p2[x] = '\0';
            strcpy(data_after,s+j);
            if(s[k] == '*')
                multiply(p1,p2);//곱셈 연산
            else division(p1,p2);// 나눗셈 연산
            strcpy(s+i+1,p1);//계산후 값을 붙여넣기
            strcat(s,data_after);//연산자의 후위값들을 붙여넣기
        }
        else{
            for(k=1;k<strlen(s) &&s[k] !='+' &&s[k] !='-';k++);
            
            if( s[k] =='+' || s[k] =='-'){
                while(check_oper(s) !=0); // (+-,++,--,-+)연산처리
                for(k=1; k<strlen(s) && s[k] !='+' && s[k] !='-';k++);
                //p1 찾아 저장
                for(x=0,i=k-1; i>=0 && s[i] !='+' && s[i] !='-'; i--,x++)
                    p1[x] = s[i];
                p1[x] = '\0';
                change(p1);
                //p2 찾아 저장
                for(x=0,j=k+1;j<strlen(s) && s[j] !='+' && s[j] !='-'; j++,x++)
                    p2[x] = s[j];
                p2[x] = '\0';
                strcpy(data_after,s+j);
                //plus minus 연산하기
                if((s[k] == '+' && s[i] !='-') || (s[k] == '-' && s[i] =='-')){
                    plus(p1,p2);
                    if(s[i] =='-'){ // p1과 p2모두 음수 인경우 처리
                        change(p1); // p1값을 뒤집어서
                        strcat(p1,"-"); // - 음수를 붙여넣음
                        change(p1);
                    }
                }
                else{
                    minus(p1,p2);
                    if(s[k] =='+'){ // p1이 음수고 p2가 양수인 경우
                        change(p1); // 위와 동일
                        strcat(p1,"-");
                        change(p1);
                    }
                }
                strcpy(s,p1);
                strcat(s,data_after);
            }
        }
    }
    return 0;
}
//곱셈연산
void multiply(char *p1,char *p2)
{
    int k,i,j,x=0,y=0,flag=1;//k :carry x,y : . position
    char dap[MAX]={0},after[MAX]={0};
    if(p2[0] == '-'){ // p2가 음수인지 검사
        flag=-1; // 음수인것을 저장해놓음
        strcpy(p2,p2+1); // - 부호제거
    }
    change(p1);
    change(p2);
    for(i=0;i<strlen(p1);i++) //소수점 위치 파악
        if(p1[i] =='.')
            x=i;
        for(i=0;i<strlen(p2);i++) //소수점 위치 파악
            if(p2[i] =='.')
                y=i;
            if(x!=0) // 소수점 제거
                strcpy(p1+x,p1+x+1);
            if(y!=0) // 소수점 제거
                strcpy(p2+y,p2+y+1);
            for(i=0;i<strlen(p1);i++) // 곱셈 연산
                for(j=0;j<strlen(p2);j++){
                    dap[i+j] += (int)(p1[i]-'0') * (int)(p2[j] -'0');
                    dap[i+j+1] +=dap[i+j] /10;
                    dap[i+j] %=10;
                }
                for(k=0;k<i+j+1;k++)
                    dap[k] +='0';
                dap[i+j] = '\0';
                for(k=0,i=0;strlen(dap)>i;i++){ // 캐리 계산
                    if(dap[i] >='0')
                        dap[i] -= '0';
                    k = dap[i] / 10;
                    dap[i+1] +=k;
                    dap[i] = dap[i] % 10 + '0';
                }
                if((x+y) !=0){ //소수점 위치에 소수점 넣기
                    strcpy(after,dap+x+y);
                    strcpy(dap+x+y,".");
                    strcat(dap,after);
                }
                change(dap);
                while(dap[0] == '0' && strlen(dap)!=1){ // 0 제거
                    if(dap[1] == '.')
                        break;
                    strcpy(dap,dap+1);
                }
                if(flag==-1){ // 음수 처리
                    change(dap);
                    strcat(dap,"-");
                    change(dap);
                }
                strcpy(p1,dap);
}
//나눗셈 연산
void division(char *p1,char *p2)
{
    char num[MAX]={'1'},dap[MAX]={0},num_10[3]="10",data[MAX]={0};
    int i,j,flag=1,point=0;
    for(i=0;i<51;i++)
        dap[i] ='0';
    if(p2[0] == '-'){ // p2가 음수인지 확인
        strcpy(p2,p2+1);
        flag=-1;
    }
    change(p2);
    for(i=0;p2[i] !='.' && i<51;i++); // 소수점 위치 파악
    if(p2[i] == '.'){
        point = i;
        strcpy(p2+point,p2+point+1);
    }
    change(p2);
    for(i=1;i<strlen(p2);i++,point--) // p2문자수와 같게 세팅 p2가 2312일 경우1000으로 만듦
        num[i] ='0';
    num[i] ='\0';
    //나눗셈 계산
    strcpy(data,p2);
    for(i=0; i<51 && check_zero(num);j=0){
        while(j<9 && check_zero(num) && check_value(num,p2) != 1 && num[0]>'-'){
            ++j;
            minus(num,p2);
            dap[i] +=1;
        }
        
        if(check_zero(num))
            multiply(num,num_10);
        if(check_value(num,p2)!=1)
            multiply(num,num_10);
        i++;
    }
    
    strcpy(data,dap+point+1);
    strcpy(dap+point+1,".");
    strcat(dap,data);
    change(dap);
    
    change(dap);
    if(flag==-1){ //음수 처리
        change(dap);
        strcat(dap,"-");
        change(dap);
    }
    multiply(p1,dap); // p1과 1/p2값을 곱한다.
}

//덧셈 연산
void plus(char *p1,char *p2)
{
    char p1_point[MAX]={0},p2_point[MAX]={0};
    int i,k,min=0;
    cut(p1,p2,p1_point,p2_point); //p1 p2의 소수와 정수를 나눔
    change(p1);
    change(p2);
    if(strlen(p1_point)<=strlen(p2_point)) //p1과 p2의 작은 값 저장
        min=strlen(p1_point);
    else min=strlen(p2_point);
    
    if(strlen(p1_point) >= strlen(p2_point))// 큰값과 작은값 자리 교체
        swap(p1_point,p2_point);
    strcat(p1_point,p2_point+min); // 계산 안해도 되는 부분 복사
    
    for(i=0;i<min;i++)
        p1_point[i] += p2_point[i] - '0';
    for(k=0,i=strlen(p1_point)-1;i>=0;i--){//캐리 계산
        p1_point[i] +=k;
        p1_point[i] -='0';
        k=p1_point[i]/10;
        p1_point[i] = p1_point[i] %10 +'0';
    }
    
    if(strlen(p1)<=strlen(p2))
        min=strlen(p1);
    else min=strlen(p2);
    if(strlen(p1) >= strlen(p2))
        swap(p1,p2);
    strcat(p1,p2+min);
    for(i=0;i<min;i++)
        p1[i] += p2[i] - '0';
    p1[0]+=k;
    for(i=0;strlen(p1)>i;i++){//캐리 계산
        if(p1[i] >='0')
            p1[i] -= '0';
        k = p1[i] / 10;
        p1[i+1] +=k;
        p1[i] = p1[i] % 10+'0';
    }
    change(p1);
    if(p1_point[0] !='\0'){ // 소수점 붙이기
        strcat(p1,".");
        strcat(p1,p1_point);
    }
}
//뺄셈 연산
void minus(char *p1,char *p2)
{
    char p1_point[MAX]={0},p2_point[MAX]={0},tmp[MAX],tmp1[MAX];
    int i,k,max=0,flag=1,point=0;
    cut(p1,p2,p1_point,p2_point);
    // 넘겨받은 p1값이 p2보다 클때 음수 표시
    if((strlen(p1) < strlen(p2)) ||
        (strlen(p1) == strlen(p2) && strcmp(p1,p2) == -1)||
        (strlen(p1) == strlen(p2) && strcmp(p1,p2) ==0 && strlen(p1_point)== strlen(p2_point) && strcmp(p1_point,p2_point) ==-1))
        flag=-1;
    if(flag==-1){// 음수면 계산후 음수 붙이기
        minus(p2,p1);
        strcpy(tmp1,p2);
    }
    // 소수점자리 밑에 남은 수들 0 붙이기 123.123과 12.12면 12.120으로 만들기
    if(strlen(p1_point)>=strlen(p2_point)){
        point=strlen(p1_point);
        for(i=strlen(p2_point);i<point;i++){
            p2_point[i] ='0';
            p2_point[i+1]='\0';
        }
    }
    else { // 마찬가지 0붙이기
        point=strlen(p2_point);
        for(i=strlen(p1_point);i<point;i++){
            p1_point[i] ='0';
            p1_point[i+1]='\0';
        }
    }
    strcat(p1,p1_point);
    strcat(p2,p2_point);
    change(p1);
    change(p2);
    max = strlen(p1);
    for(i=0;i<max;i++){
        p1[i] = p1[i]+10-p2[i];
        p1[i+1] -=1;
        if(p1[i] < '0')
            p1[i] +='0';
    }
    for(k=0,i=0;i<max;i++){ //캐리 처리
        if(p1[i] >='0')
            p1[i] -= '0';
        k = p1[i] / 10;
        p1[i+1] +=k;
        p1[i] = (p1[i] % 10) +'0';
    }
    if(point !=0){ // 소수점 위치에 소수점 붙여넣기
        strcpy(tmp,p1+point);
        p1[point]='.';
        strcpy(p1+point+1,tmp);
    }
    change(p1);
    // 시작 0 없애기
    while(p1[0] == '0' && p1[1] !='.'){
        if(strlen(p1) != 1){
            strcpy(tmp,p1+1);
            strcpy(p1,tmp);
        }
        else break;
    }
    if(flag == -1){ //음수 처리
        change(tmp1);
        strcat(tmp1,"-");
        change(tmp1);
        strcpy(p1,tmp1);
    }
    change(p2);
}
// +- ++ -- -+ 일때
int check_oper(char *s1){
    int i,flag=0;
    for(i=0;s1[i] !='\0';i++){
        if(s1[i] == '+' && s1[i+1] =='-' || s1[i] =='-' && s1[i+1]=='+'){
            s1[i] = '-';
            strcpy(s1+i+1,s1+i+2);
            flag++;
        }
        if(s1[i] == '+' &&s1[i+1] =='+' || s1[i] == '-' && s1[i+1] == '-'){
            s1[i] ='+';
            strcpy(s1+i+1,s1+i+2);
            flag++;
        }
    }
    return flag;
}

int ChangePostfix(Postfix *nums, Postfix *num, int cnt) {
    
    char stack[100] = { 0, };
    int i=0, j=0, Psp=0, Ssp=0;

    for (i = 0; i < cnt; i++) {
        
        if (nums[i].set == 1) {
            num[Psp].n = nums[i].n;
            num[Psp].set = 1;
            Psp++;
        }
        else {
            if (nums[i].n == ')') {
            
                for (j = Ssp - 1; stack[j] != '('; j--) {
                    num[Psp].n = stack[j];
                    num[Psp].set = 0;
                    Psp++;
                    stack[j] = 0;
                }
                Ssp = j;
                stack[j] = 0;
                if (Ssp >= 1) {
                    if (stack[Ssp - 1] == '-' && ( stack[Ssp - 2] == '(' || stack[Ssp - 2] == '+' || stack[Ssp - 2] == '-' || stack[Ssp - 2] == '*' || stack[Ssp - 2] == '/' || stack[Ssp - 2] == '^' || stack[Ssp - 2] == 6 || stack[Ssp - 2] == '%')) {
                        num[Psp].n = -1;
                        num[Psp].set = 1;
                        Psp++;
                        num[Psp].n = '*';
                        num[Psp].set = 0;
                        Psp++;
                        stack[Ssp - 1] = 0;
                        Ssp--;
                    }
                }
                
            }
            else if (nums[i].n == '(') {
    
                if (nums[i - 1].n == ')' || ('0' <= nums[i-1].n && nums[i-1].n <= '9')) {
                    if (Ssp != 0) {
                        for (j = Ssp - 1; j >= 0 && stack[j] != '(' && stack[j] != '+' && stack[j] != '-'; j--) {
                            num[Psp].n = stack[j];
                            num[Psp].set = 0;
                            Psp++;
                            stack[j] = 0;
                        }
                        j++;
                        Ssp = j;
                        
                    }
                    stack[Ssp++] = '*';
                }
                
                stack[Ssp++] = (char)nums[i].n;

            }
            else if (nums[i].n == '!' || nums[i].n == 1) {
                if (Ssp != 0) {
                    for (j = Ssp - 1; j >= 0 && stack[j] != '(' && stack[j] != '+' && stack[j] != '-' && stack[j] != '*' && stack[j] != '/' && stack[j] != '^' && stack[j] != 6 && stack[j] != '%'; j--) {
                        num[Psp].n = stack[j];
                        num[Psp].set = 0;
                        Psp++;
                        stack[j] = 0;
                    }
                    j++;
                    Ssp = j;
                }
                stack[Ssp++] = (char)nums[i].n;
            }
            else if (nums[i].n == '^' || nums[i].n == 6) {

                if (Ssp != 0) {
                    for (j = Ssp - 1; j >= 0 && stack[j] != '(' && stack[j] != '+' && stack[j] != '-' && stack[j] != '*' && stack[j] != '/' && stack[j] != '^' && stack[j] != 6 && stack[j] != '%'; j--) {
                        num[Psp].n = stack[j];
                        num[Psp].set = 0;
                        Psp++;
                        stack[j] = 0;
                    }
                    j++;
                    Ssp = j;
                }
                stack[Ssp++] = (char)nums[i].n;

            }
            else if (nums[i].n == '*' || nums[i].n == '/' || nums[i].n == '%') {


                if (Ssp != 0) {
                    for (j = Ssp - 1; j >= 0 && stack[j] != '(' && stack[j] != '+' && stack[j] != '-'; j--) {
                        num[Psp].n = stack[j];
                        num[Psp].set = 0;
                        Psp++;
                        stack[j] = 0;
                    }
                    j++;
                    Ssp = j;
                }
                stack[Ssp++] = (char)nums[i].n;
                //stack[Ssp++] = 'n';
            }
            else if (nums[i].n == '+' || nums[i].n == '-') {

                if (Ssp != 0) {
                    for (j = Ssp - 1; j >= 0 && stack[j] != '('; j--) {
                        num[Psp].n = stack[j];
                        num[Psp].set = 0;
                        Psp++;
                        stack[j] = 0;
                    }
                    j++;
                    Ssp = j;
                }


                stack[Ssp++] = (char)nums[i].n;

            }
        }
    }
    

    for (j = Ssp-1; j >= 0; j--) {
        num[Psp].n = stack[j];
        num[Psp].set = 0;
        Psp++;
        stack[j] = 0;
    }

    return Psp;
}
