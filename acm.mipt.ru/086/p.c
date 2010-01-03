char s[400];int a[400];main(i,j,n){scanf(" %s",s);for(n=a[0]=1;;n++){for(i=j=0;
i<300;i++,j/=10)a[i]=(j+=a[i]*n)%10;for(i=300;!a[--i];);for(j=0;s[j]&&i>=0&&a[i]
+'0'==s[j];i--,j++);if(!s[j]&&i<0)break;}printf("%d\n",n);return 0;}
