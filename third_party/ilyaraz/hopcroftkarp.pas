{$I-,Q-,R-,S-}
var n,m,k,i,x,y,cnt,qh,qt,j:longint;
    g:array [1..1000,1..1000] of boolean;
    a,b,l,q:array [0..1000] of longint;
    f:array [0..1000] of boolean;
function dfs(u:longint):boolean;
var j:longint;
begin
  dfs:=true;
  if u=0 then
    exit;
  f[u]:=false;
  for j:=1 to m do
    if g[u,j] and f[b[j]] and (l[b[j]]=l[u]+1) and dfs(b[j]) then
    begin
      b[j]:=u;
      a[u]:=j;
      exit;
    end;
  dfs:=false;
end;
procedure put(x,d:longint);
begin
  f[x]:=true;
  l[x]:=d;
  q[qt]:=x;
  inc(qt);
end;
function get:longint;
begin
  get:=q[qh];
  inc(qh);
end;
begin
  read(n,m,k);
  fillchar(g,sizeof(g),false);
  for i:=1 to k do
  begin
    read(x,y);
    g[x,y]:=true;
  end;
  fillchar(a,sizeof(a),0);
  fillchar(b,sizeof(b),0);
  cnt:=0;
  repeat
    qh:=0;
    qt:=0;
    fillchar(l,sizeof(l),63);
    fillchar(f,sizeof(f),0);
    for i:=1 to n do
      if a[i]=0 then
        put(i,0);
    while qh<qt do
    begin
      x:=get;
      if l[x]=l[0] then
        break;
      for j:=1 to m do
        if g[x,j] and not f[b[j]] then
          put(b[j],l[x]+1);
    end;
    if not f[0] then
      break;
    for i:=1 to n do
      if (a[i]=0) and dfs(i) then
        inc(cnt);
  until false;
  writeln(cnt);
end.
