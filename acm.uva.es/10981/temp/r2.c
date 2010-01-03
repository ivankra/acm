main(i,j,t){
  printf("1000\n");
  for(t=0;t<1000;t++){
    for(i=0;i<5;i++)putchar('a'+(rand()%3));putchar('\n');
    printf("%c\n",'a'+(rand()%3));
  }
}