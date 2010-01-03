const
	MaxSize = 200;
	Infinity = MaxLongint div 8;
type
	TIndex = Longint;
	TData = Longint;
	TGraph = array [1..MaxSize, 1..MaxSize] of TData;
	TUsed = array [1..MaxSize] of Boolean;
	TLabel = array [1..MaxSize] of TData;
	TLink = array [1..MaxSize] of TIndex;
var
	N, M: TIndex;
	Graph: TGraph;
	UsedX, UsedY: TUsed;
	LabelX, LabelY: TLabel;
	Link: TLink;

function FindPath(i: TIndex): Boolean;
var
	j: TIndex;
begin
	Result := true;
	if i = 0 then Exit;
	UsedX[i] := true;
	for j := 1 to M do
		if (Graph[i, j] > 0) and (Graph[i, j] = LabelX[i] + LabelY[j]) and not UsedY[j] then
		begin
			UsedY[j] := true;
			if (Link[j] = 0) or FindPath(Link[j]) then
			begin
				Link[j] := i;
				Exit;
			end;
		end;
	Result := false;
end;
procedure Main;
var
	i, j, k: TIndex;
	Delta: TData;
	Total: TData;
begin
	Readln(N, M);
	for i := 1 to N do
		for j := 1 to M do
			Read(Graph[i, j]);
	FillChar(Link, SizeOf(Link), 0);
	FillChar(LabelX, SizeOf(LabelX), 0);
	FillChar(LabelY, SizeOf(LabelY), 0);
	for i := 1 to N do
		for j := 1 to M do
			if LabelX[i] < Graph[i, j] then
				LabelX[i] := Graph[i, j];
	for k := 1 to N do
		repeat
			FillChar(UsedX, SizeOf(UsedX), 0);
			FillChar(UsedY, SizeOf(UsedY), 0);
			if FindPath(k) then Break;
			Delta := Infinity;
			for i := 1 to N do
				if UsedX[i] then
					for j := 1 to M do
						if not UsedY[j] and (Graph[i, j] > 0) and (LabelX[i] + LabelY[j] - Graph[i, j] < Delta) then
							Delta := LabelX[i] + LabelY[j] - Graph[i, j];
			if Delta = 0 then Break;
			for i := 1 to N do
				if UsedX[i] then
					Dec(LabelX[i], Delta);
			for i := 1 to M do
				if UsedY[i] then
					Inc(LabelY[i], Delta);
		until false;
	Total := 0;
	for i := 1 to N do
		Inc(Total, LabelX[i]);
	for i := 1 to M do
		Inc(Total, LabelY[i]);
	Writeln(Total);
end;
begin
	Main;
end.
