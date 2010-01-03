(* (C) 2003 Andrew Lopatin, Kitten Computing *)(* Solution for task "find the maximal covered point" *){$O-,Q+,R+}uses sysutils, math;

const MaxN=8000;

var p:array [1..MaxN*4] of integer;
    x, y:array [1..MaxN*4] of integer;
    f:array [1..MaxN*4] of byte;


function less (i, j:integer):boolean;
begin
  less:=(y[i]<y[j]) or
        (
         (y[i]=y[j]) and (
          (f[i]<f[j]) or
          (
           (f[i]=f[j]) and (
            x[i]<x[j]
           )
          )
         )
        );
end;

procedure qsort (l, r:integer);
var i, j, x, y:integer;
begin
  if l>=r then exit;
  i:=l; j:=r; x:=p[(l+r) shr 1];
  repeat
    while less (p[i], x) do inc (i);
    while less (x, p[j]) do dec (j);
    if i<=j then begin
      y:=p[i]; p[i]:=p[j]; p[j]:=y;
      inc (i); dec (j);
    end;
  until i>j;
  qsort (l, j);
  qsort (i, r);
end;


type pnode=^tnode;
     tnode=record
       l, r:pnode;
       x, y, m, c, g, mx:integer;
     end;

const minint=-maxint-1;
      null:tnode=(l:@null; r:@null; x:minint; y:minint; m:0; c:0; g:0; mx:0);

var maxc, mx, my:integer;


procedure renew (t:pnode);
begin
  if t.l.m>t.l.c+t.g then begin t.m:=t.l.m; t.mx:=t.l.mx  end
                     else begin t.m:=t.l.c+t.g; t.mx:=t.x end;
  if t.l.c+t.g+t.r.m>t.m then begin t.m:=t.l.c+t.g+t.r.m; t.mx:=t.r.mx end;
  t.c:=t.l.c+t.g+t.r.c;
end;


procedure split (t:pnode; x, g:integer; var l, r:pnode);
begin
  if t=@null then begin l:=@null; r:=@null end else begin
    if (x<t.x) or ((x=t.x) and (g>t.g))
      then begin split (t.l, x, g, l, r); t.l:=r; r:=t end
      else begin split (t.r, x, g, l, r); t.r:=l; l:=t end;
    renew (t);
  end;
end;


function merge (l, r:pnode):pnode;
begin
  if l=@null then merge:=r else
  if r=@null then merge:=l else begin
    if l.y>r.y then begin l.r:=merge (l.r, r); merge:=l end
               else begin r.l:=merge (l, r.l); merge:=r end;
    renew (Result);
  end;
end;

procedure insert (var t:pnode; x, y, g:integer);
var tmp:pnode;
begin
  if y>t.y then begin
    new (tmp); split (t, x, g, tmp.l, tmp.r); t:=tmp;
    t.x:=x; t.y:=y; t.g:=g;
  end else
    if (x<t.x) or ((x=t.x) and (g>t.g)) then insert (t.l, x, y, g)
                                        else insert (t.r, x, y, g);
  renew (t);
end;


procedure delete (var t:pnode; x, g:integer);
begin
  assert (t<>@null);
  if (x<t.x) or ((x=t.x) and (g>t.g)) then delete (t.l, x, g) else
  if (x>t.x) or ((x=t.x) and (g<t.g)) then delete (t.r, x, g) else
  t:=merge (t.l, t.r);
  renew (t);
end;


var i, n:integer;
    t:pnode=@null;

begin
  assign (input, 'windows.in'); reset (input);
  assign (output, 'windows.out'); rewrite (output);
  read (n);
  for i:=1 to n do begin
    read (x[i], y[i]); f[i]:=1; 
    read (x[i+2*n], y[i+2*n]); f[i+2*n]:=3;
    x[i+n]:=x[i+2*n]; y[i+n]:=y[i]; f[i+n]:=0;
    x[i+3*n]:=x[i]; y[i+3*n]:=y[i+2*n]; f[i+3*n]:=2;
  end;
  n:=n shl 2; for i:=1 to n do p[i]:=i;
  qsort (1, n);
  maxc:=0;
  for i:=1 to n do begin
    if f[p[i]]<2 then insert (t, x[p[i]], random (1000000000), ord (f[p[i]] in [1,2])*2-1)
                 else delete (t, x[p[i]], ord (f[p[i]] in [1,2])*2-1);
    if t.m>maxc then begin maxc:=t.m; mx:=t.mx; my:=y[p[i]] end;
  end;
  writeln (maxc);
  writeln (mx, ' ', my);
end.
