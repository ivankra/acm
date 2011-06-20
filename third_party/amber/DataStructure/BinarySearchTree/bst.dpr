type
	TIndex=Longint;
	TValue=TIndex;
	PNode=^TNode;
	TNode=record
		Value:TValue;
		Times:TIndex;
		Left,Right:PNode;
	end;
	TBST=object
     //	private
		Root:PNode;
		function GetMinimum(Node:PNode):PNode;
		function GetMaximum(Node:PNode):PNode;
		function Find(Node:PNode;Value:TValue):PNode;
	public
		procedure Init;
		procedure Insert(Value:TValue);
		function Minimum:TValue;
		function Maxnimum:TValue;
		procedure Delete(Value:TValue);
	end;

function TBST.GetMinimum(Node:PNode):PNode;
begin
	while Node^.Left<>nil do
		Node:=Node^.Left;
	Result:=Node;
end;

function TBST.GetMaximum(Node:PNode):PNode;
begin
	while Node^.Right<>nil do
		Node:=Node^.Right;
	Result:=Node;
end;

function TBST.Minimum:TValue;
begin
	Result:=GetMinimum(Root).Value;
end;
function TBST.Maxnimum:TValue;
begin
	Result:=GetMaximum(Root).Value;
end;

function TBST.Find(Node:PNode;Value:TValue):PNode;
begin
	while Node<>nil do
		if Value<Node^.Value then
			Node:=Node^.Left
		else if Node^.Value<Value then
			Node:=Node^.Right
		else if Node^.Value=Value then 
			Break;
	Result:=Node;
end;

procedure TBST.Insert(Value:TValue);
var 
	Node,Cur,Father:PNode;
begin
	Node:=Find(Root,Value);
	if Node<>nil then
	begin
		Inc(Node^.Times);
		Exit;
	end;

	New(Cur);
	Cur^.Value:=Value;
	Cur^.Left:=nil;
	Cur^.Right:=nil;
	Cur^.Times:=1;

	Node:=Root;
        Father:=nil;
	while Node<>nil do
	begin
		Father:=Node;
		if Value<Node^.Value then
			Node:=Node^.Left
		else if Node^.Value<Value then
			Node:=Node^.Right;
	end;

	if Root=nil then 
		Root:=Cur
	else if Value<Father^.Value then
		Father^.Left:=Cur
	else if Father^.Value<Value then
		Father^.Right:=Cur;
end;


procedure TBST.Delete(Value:TValue);
var 
	Node,Cur,Father,CurFather:PNode;
begin
        Node:=Root;
        Father:=nil;
	while (Node<>nil) and (Node^.Value<>Value) do
        begin
                Father:=Node;
		if Value<Node^.Value then
			Node:=Node^.Left
		else if Node^.Value<Value then
			Node:=Node^.Right;
        end;

	if Node=nil then 
		Exit
	else if Node^.Times>1 then
	begin
		Dec(Node^.Times);
		Exit;
	end;
        
	if (Node^.Left<>nil) and (Node^.Right<>nil) then
	begin
		CurFather:=Node;
		Cur:=Node^.Left;
		while Cur^.Right<>nil do
		begin
			CurFather:=Node;
			Cur:=Cur^.Right;
		end;
		Node^.Value:=Cur^.Value;
		Node:=Cur;
		Father:=CurFather;
	end;

	if Node^.Left<>nil then
		Cur:=Node^.Left
	else 
		Cur:=Node^.Right;
	
	if Node=Root then Root:=Cur
	else if Node=Father^.Left then
		Father^.Left:=Cur
	else 
		Father^.Right:=Cur;
	Dispose(Node);
end;

procedure TBST.Init;
begin
	Root:=nil;
end;
var BST:TBST;
procedure Main;
begin
        BST.Init;
        BST.Insert(30); 
        BST.Insert(30);
        BST.Insert(35);
        BST.Insert(5);
        BST.Insert(2);
        BST.Insert(32);
        BST.Insert(80);
        BST.Insert(60);
        BST.Insert(85);
        BST.Insert(31);
        BST.Insert(33);

        BST.Delete(35);
        BST.Delete(30);
        BST.Delete(30);
        BST.Delete(5);
        BST.Delete(2);
        Assign(Output,'o.txt');
	Rewrite(Output);
 Writeln(         BST.Root^.Value);
	Close(Output);
end;

begin
        Main;        
end.
