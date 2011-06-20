(* (C) 2003 Andrew Lopatin, Kitten Computing *)
(* Solution for Task K *)
{$o+,q-,r-}
{$apptype console}
uses sysutils;
var u:array [1..262144] of integer;

function up (p:integer):integer;
begin
  if u[p]<>p then u[p]:=up (u[p]);
  up:=u[p];
end;


type pnode=^tnode;
     tnode=record
       l, r:pnode;
       s, v, y:integer;
     end;


const minint=-maxint-1;
      null:tnode=(l:@null;r:@null;s:0;v:minint;y:minint);


procedure split (t:pnode; x:integer; var l, r:pnode);
begin
  if t=@null then begin l:=t; r:=t end else
  if x<=t.l.s then begin split (t.l, x, l, r); t.l:=r; dec (t.s, x); r:=t end 
              else begin split (t.r, x-t.l.s-1, l, r); t.r:=l; 
                         t.s:=t.l.s+t.r.s+1; l:=t end;
end;


function merge (l, r:pnode):pnode;
begin
  if l=@null then merge:=r else
  if r=@null then merge:=l else
  if l.y>r.y then begin inc (l.s, r.s); l.r:=merge (l.r, r); merge:=l end
             else begin inc (r.s, l.s); r.l:=merge (l, r.l); merge:=r end;
end;


procedure insert (var t:pnode; x, v, y:integer);
var tmp:pnode;
begin
  if y>t.y then begin new (tmp); split (t, x, tmp.l, tmp.r); t:=tmp; t.v:=v;
                      t.y:=y; t.s:=t.l.s+t.r.s+1 end else
  if x<=t.l.s then begin insert (t.l, x, v, y); inc (t.s) end
              else begin insert (t.r, x-t.l.s-1, v, y); inc (t.s) end;
end;

procedure display (t:pnode);
begin
  if t=@null then exit;
  display (t.l);
  writeln (t.v);
  display (t.r);
end;


var t:array [1..262144] of pnode;
    i, n, m, p, s, z:integer;

begin
  assign (input, 'key.in'); reset (input);
  assign (output, 'key.out'); rewrite (output);
  read (n, m); for i:=1 to m+n do begin u[i]:=i;t[i]:=@null end;
  for i:=1 to n do begin
    read (p); s:=up (p);
    repeat
      z:=s+t[s].s;
      if t[z]<>@null then begin t[s]:=merge (t[s], t[z]); u[z]:=s; t[z]:=@null end
                     else break;
    until false;
    insert (t[s], p-s, i, random (1000000000));
    u[z]:=s;
  end;
  z:=0;
  for i:=m downto 1 do
    if t[i]<>@null then begin z:=i+t[i].s-1; break end;
  writeln (z);
  i:=1; while i<=z do begin
    if t[i]=@null then begin writeln(0); inc (i) end
                  else begin display (t[i]); inc (i, t[i].s) end;
    flush (output);
  end;
end.