#include <stdio.h>
#include <string.h>

struct tile{
 char letter;
 int num;
};

void parse (struct tile data[14], const char inp[]){
 char holder;
 int i = strlen(inp)-1, index = 0;
	
 while (index < 14){
  if (inp[i] >= 'a') {holder = inp[i--];}
  else{
   data[index].letter = holder;
   data[index].num = inp[i] - '0';
   index++;
   i--;
  }
 }
}

int sort (struct tile data[14], int len){
 int i, flag = 1, m = 0;
 struct tile holder;
	
 while (flag == 1){
  flag = 0;
  for (i=0; i<len-1; i++){
   if (data[i].letter > data[i+1].letter){
    holder.letter = data[i].letter;
    holder.num = data[i].num;
    data[i].letter = data[i+1].letter;
    data[i].num = data[i+1].num;
    data[i+1].letter = holder.letter;
    data[i+1].num = holder.num;
    flag = 1;
   }
  }
 }
  
 for (i=0; i<len-1; i++){
  if (data[i].letter != data[i+1].letter){
   m = i+1;
   break;
  }
 }
	
 flag = 1;
 while (flag == 1){
  flag = 0;
  for (i=0; i<m-1; i++){
   if (data[i].num > data[i+1].num){
    holder.num = data[i].num;
    data[i].num = data[i+1].num;
    data[i+1].num = holder.num;
    flag = 1;
   }
  }
 }
	
 flag = 1;
 while (flag == 1){
  flag = 0;
  for (i=m; i<len-1; i++){
   if (data[i].num > data[i+1].num){
    holder.num = data[i].num;
    data[i].num = data[i+1].num;
    data[i+1].num = holder.num;
    flag = 1;
   }
  }
 }
	
 return m;
}

int _7PairsPossible(struct tile data[14], int m){ //checked
 int i, count = 0; 
 if (m%2 == 1) {return 0;}
 else{
  
  for (i=0; i<7; i++){
   if (data[2*i].num == data[2*i+1].num) {count++;}
  }
  
  if (count == 7) {return 1;}
  else{return 0;}
 }
}

int _4TripletsPossible(struct tile data[14]){ //checked
 int i, count = 0; 
  
 for (i=0; i<4; i++){
  if (data[3*i].num == data[3*i+1].num && data[3*i].num == data[3*i+2].num) {count++;}
 }
  
 if (count == 4) {return 1;}
 else {return 0;}
}

int _5TerminalsPossible(struct tile data[14], int arr[4][4]){ //slight difference
 int i, count = 0, flag = 0, index = 0;
 struct tile triplets[14];
 
 for (i=0; i<14; i++){
  triplets[i].letter = 'e';
  triplets[i].num = '0';
 }
 
 if (data[12].num == 1 || data[12].num == 9) {flag = 1;}
  
 for (i=0; i<4; i++){
  if (arr[i][1] == 1 || arr[i][1] == 9 || arr[i][2] == 1 || arr[i][2] == 9 || arr[i][3] == 1 || arr[i][3] == 9) {count++;}
 }
 
 for (i=0; i<4; i++){
  if (arr[i][1] == arr[i][2] && arr[i][1] == arr[i][3]){
   triplets[index].letter = arr[i][0];
   triplets[index].num = arr[i][1];
   index++;
  }
 }
 
 int p = sort(triplets, 5);
 
 int q = 0;
 for (i=0; i<4; i++){
  if (triplets[i].num == 1 || triplets[i].num == 9) {q++;}
 }
 
 int bool = 0;
 if (index == 3){
  if (triplets[0].num == triplets[1].num-1 && triplets[0].num == triplets[2].num-2) {bool = 1;}
  else {bool = 0;}
 }
 else if (index == 4){
  if (p == 1){
   if (triplets[1].num == triplets[2].num-1 && triplets[1].num == triplets[3].num-2) {bool = 1;}
   else {bool = 0;}
  }
  if (p == 3){
   if (triplets[0].num == triplets[1].num-1 && triplets[0].num == triplets[2].num-2) {bool = 1;}
   else {bool = 0;}
  }
  if (p == 4){
   if (triplets[0].num == triplets[1].num-1 && triplets[0].num == triplets[2].num-2) {
    if (triplets[0].num == 1 || triplets[2].num == 9) {bool = 1;}
    else {bool = 0;}
    }
   else if (triplets[1].num == triplets[2].num-1 && triplets[1].num == triplets[3].num-2) {
    if (triplets[1].num == 1 || triplets[3].num == 9) {bool = 1;}
    else {bool = 0;}
    }
   else {bool = 0;}
  }
 }
 
 if (flag == 0) {return 0;}
 else if (count == 4) {return 1;}
 else if (count < 2) {return 0;}
 else if (index < 3) {return 0;}
 else if (index == 3) {
  if (q == count) {return 0;}
  else if (p == 3) {return bool;}
  else {return 0;}
 }
 else if (index == 4){
  if (p == 4) {return bool;}
  if (p == 2) {return 0;}
  if (p == 1) {
   if (triplets[0].num == 1 || triplets[0].num == 9) {return bool;}
   else {return 0;}
  }
  if (p == 3) {
   if (triplets[3].num == 1 || triplets[3].num == 9) {return bool;}
   else {return 0;}
  }
 }
 
 return 0;
}

int _258Possible(struct tile data[14]){ //checked
 int i, count = 0; 
  
 for (i=0; i<14; i++){
  if (data[i].num == 2 || data[i].num == 5 || data[i].num == 8) {count++;}
 }
  
 if (count == 14) {return 1;}
 else {return 0;}
}

int _4MeldsPossible(struct tile data[14], int arr[4][4]){ //slight difference in flags
 int i, row, col, flag1, flag2;
 for (row=0; row<4; row++){
  for (col=0; col<4; col++)
   {arr[row][col] = 0;}
 }
	
 for (i=0; i<12; i++){
  row = 0;
  flag1 = 0;
  while (flag1 == 0){
   if (row == 4) {return 0;}
   else if (arr[row][0] == 0){
    arr[row][0] = data[i].letter;
    arr[row][1] = data[i].num;
    flag1 = 1;
   }
   else if (arr[row][0] != data[i].letter) {row++;}
   else if (arr[row][2] == 0){
    
    flag2 = 0;
    if (arr[row][1] == data[i].num && arr[row][1] == data[i+1].num) {flag2 = 1;}
    if (arr[row][1] == data[i].num-1) {flag2 = 1;}
    
    if (flag2 == 1){
     arr[row][2] = data[i].num;
     flag1 = 1;
    }
    else {row++;}
   }
   else if (arr[row][3] != 0)
    {row++;}
   else{
    
    flag2 = 0;
    if (arr[row][1] == arr[row][2] && arr[row][1] == data[i].num) {flag2 = 1;}
    if (arr[row][1] == arr[row][2]-1 && arr[row][1] == data[i].num-2) {flag2 = 1;}
    
    if (flag2 == 1){
     arr[row][3] = data[i].num;
     flag1 = 1;
    }
    else {row++;}
   }
  }
 }
 return 1;
}

int countTypes(struct tile data[14]){ //checked
 int b=0, c=0, d=0, out, i;
	
 for (i=0; i<14; i++){
  if (data[i].letter == 'b') {b=1;}
  else if (data[i].letter == 'c') {c=1;}
  else if (data[i].letter == 'd') {d=1;}
 }
	
 out = b + c + d;
 return out;
}

int countRoots(struct tile data[14], int m){ //checked
 int count = 1, i;
	
 for (i=0; i<m-3; i++){
  if (data[i].num == data[i+1].num && data[i].num == data[i+2].num && data[i].num == data[i+3].num) {count *= 2;}
 }
	
 for (i=m; i<11; i++){
  if (data[i].num == data[i+1].num && data[i].num == data[i+2].num && data[i].num == data[i+3].num) {count *= 2;}
 }
	
 return count;
}

int getScore(const char strHand[]){ //similar
 struct tile data[14];
	
 parse (data, strHand);
 int m = sort(data, 14);
 int types = countTypes(data);
 int mult = countRoots(data, m);
	
 if (types == 1) {mult *= 4;}
 else if (types == 2) {mult *= 1;}
 else {return 0;}
	
 int a = _7PairsPossible(data, m);
 if (a == 1){return 4*mult;}
	
 int flag1 = _258Possible(data);
	
 int start, stop;
 if (m%3 == 2) {start = 0; stop = m-1;}
 else if (m%3 == 0) {start = m; stop = 13;}
 else {return 0;}
	
 int i, flag2 = 0, flag3 = 0;
 struct tile holder;
 int arr[4][4];
	
 for (i=start; i<stop; i++){
  sort(data, 14);
  if (data[i].num == data[i+1].num){
   
   holder.num = data[13].num;
   holder.letter = data[13].letter;
   data[13].num = data[i+1].num;
   data[13].letter = data[i+1].letter;
   data[i+1].num = holder.num;
   data[i+1].letter = holder.letter;
   
   holder.num = data[12].num;
   holder.letter = data[12].letter;
   data[12].num = data[i].num;
   data[12].letter = data[i].letter;
   data[i].num = holder.num;
   data[i].letter = holder.letter;
   
   sort(data, 12);
   int d = _4MeldsPossible(data, arr);
   if (d == 1){
    flag2 = 1;
    
    int b = _5TerminalsPossible(data, arr);
    if (b == 1){return 4*mult;}
    
    int c = _4TripletsPossible(data);
    if (c == 1){flag3 = 1;
    }
   }
  }
 }
 if (flag2 == 0) {return 0;}
 else if (flag3 == 0) {return 1*mult;}
 else if (flag1 == 1) {return 8;}
 else {return 2*mult;}
}

int main() {
    char patternName[10][30] = {
            "Chicken Hand",
            "Full Flush",
            "All Triplets",
            "Pure Triplets",
            "2/5/8 Triplets",
            "Terminals in All Sets",
            "Pure Terminals in All Sets",
            "Seven Pairs",
            "Pure Seven Pairs",
            "Not Winning"
    };

    int secCount[10] = {0};
    int secWA[10] = {0};
    int WA = 0;
    int hitWin = 0;
    int hitLose = 0;

    for (int i = 0; i < 10;) {
        char strHand[30];
        int score;
        scanf("%s", strHand);
        if (*strHand == 'n') {
            i++; continue;
        }
        secCount[i]++;
        scanf("%d", &score);
        int testScore = -1;
        testScore = getScore(strHand);
        if (testScore != score) {
            if (WA == 0) {
                printf("The following is some testcase you fail\n");
                printf("strHand - Expected Answer -  Your Answer\n");
            }
            secWA[i]++;
            WA++;
            if (secWA[i] <= 1) {
                printf("%-28s  %-3d  %d\n", strHand, score, testScore);
            }
        }
        if (testScore > 0 && score > 0) hitWin++;
        else if (testScore == 0 && score == 0) hitLose++;
    }

    if (WA == 0) {
        printf("Congratulation! You pass all the testcase.\n");
    }
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        printf("%-27s[%6.2f%%]\n", patternName[i], (double) (secCount[i] - secWA[i]) / secCount[i] * 100);
    }
    printf("\n");
    double hitRate = (double) hitWin / 26000 / 2 + (double) hitLose / 4000 / 2;
    printf("Determine Winning or Not   [%6.2f%%]\n", hitRate * 100);
    printf("\n");

    int score = 0;
    for (int i = 0; i < 10; ++i) {
        int ps = (secCount[i] - secWA[i]) * 100 / secCount[i];
        if (ps > 95) score += ps - 95;
    }
    int lowerBound = (30000 - WA) * 100 / 30000;
    if (lowerBound >= 90) score += 90;
    else score += lowerBound;
    score -= 35;
    int hitBound = (int) (140 * (hitRate - 0.5 > 0 ? hitRate - 0.5 : 0));
    if (score < hitBound) score = hitBound;
    else if (score > hitBound + 35) score = hitBound + 35;

    printf("Total Score: %d", score);
    return 0;
}
