{
	Author: Amber
	Algorithm: Disjoint
	Special method: N/A
	Tested Problems: N/A
}
program Source_Lib_Disjoint(Input,Output);
const
	MaxSize=1000;
type
	TIndex=Longint;
	TDisjoint=object
	public
		procedure Init(DataSize:TIndex);
		function Find(x:TIndex):TIndex;
		procedure Merge(x,y:TIndex);
	private
		Size:TIndex;
		Father:array[1..MaxSize]of TIndex;
	end;

procedure TDisjoint.Init(DataSize:TIndex);
begin
	Size:=DataSize;
	FillChar(Father,SizeOf(Father),255);
end;

function TDisjoint.Find(x:TIndex):TIndex;
begin
	if Father[x]<0 then 
		Result:=x
	else 
	begin
		Father[x]:=Find(Father[x]);
		Result:=Father[x];
	end;
end;
procedure TDisjoint.Merge(x,y:TIndex);
var
	rx,ry:TIndex;
begin
	rx:=Find(x);
	ry:=Find(y);
	if rx=ry then Exit;
	if -Father[rx]<-Father[ry] then
	begin
		Inc(Father[ry],Father[rx]);
		Father[rx]:=ry;
	end
	else 
	begin
		Inc(Father[rx],Father[ry]);
		Father[ry]:=rx;
	end;
end;
var
	N,M:TIndex;
	Disj:TDisjoint;
procedure Main;
var
	i:TIndex;
	x,y:TIndex;
begin
	Readln(N,M);
	Disj.Init(N);
	for i:=1 to M do
	begin
		Readln(x,y);
		Disj.Merge(x,y);
	end;
	for i:=1 to N do
	begin
		Readln(x,y);
		if Disj.Find(x)=Disj.Find(y) then Writeln('Equal Class')
		else Writeln('unequal Class');
	end;
end;
begin
	Main;
end.
