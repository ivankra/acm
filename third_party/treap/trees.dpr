(* (C) 2003 Andrew Lopatin, Kitten Computing *)
(* Cartesian Trees *)

type pnode=^node; 
     node=record
       l, r:pnode;
       x, y:integer;
     end;

procedure split (t:pnode; x:integer; var l, r:pnode);
begin
  if t=nil then begin l:=nil; r:=nil end else
  if x<t.x then begin split (t.l, x, l, r); t.l:=r; r:=t end
           else begin split (t.r, x, l, r); t.r:=l; l:=t end;
end;

function merge (l, r:pnode):pnode;
begin
  if l=nil then merge:=r else
  if r=nil then merge:=l else
  if l.y>r.y then begin l.r:=merge (l.r, r); merge:=l end
             else begin r.l:=merge (l, r.l); merge:=r end;
end;


procedure insert (var t:pnode; x, y:integer);
var tmp:pnode;
begin
  if (t=nil) or (y>t.y) then begin 
    new (tmp); split (t, x, tmp.l, tmp.r); t:=tmp; t.x:=x; t.y:=y
  end else if x<t.x then insert (t.l, x, y) else insert (t.r, x, y);
end;


procedure delete (var t:pnode; x:integer);
var tmp:pnode;
begin
  if t=nil then exit else
  if x<t.x then delete (t.l, x) else
  if x>t.x then delete (t.r, x) else begin
    tmp:=t; t:=merge (t.l, t.r); dispose (tmp);
  end;
end;
