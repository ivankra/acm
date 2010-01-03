{$H+}
var s:string;
    n,l,r,i:longint;
    z:array [2..100000] of longint;
begin
  assign(input,'input.txt');
  reset(input);
  assign(output,'output.txt');
  rewrite(output);
  readln(s);
  n:=length(s);
  l:=0; r:=0;
  for i:=2 to n do
    if i>r then
    begin
      z[i]:=0;
      while (i+z[i]<=n) and (s[z[i]+1]=s[z[i]+i]) do inc(z[i]);
      if z[i]>0 then begin l:=i; r:=i+z[i]-1; end;
    end
    else if z[i-l+1]<r-i+1 then z[i]:=z[i-l+1]
    else begin
      z[i]:=r-i+1;
      while (i+z[i]<=n) and (s[z[i]+1]=s[z[i]+i]) do inc(z[i]);
      l:=i; r:=i+z[i]-1;
    end;
  for i:=2 to n do writeln(z[i]);
  close(input);
  close(output);
end.

