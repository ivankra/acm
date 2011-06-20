type
	TIndex = Longint;
	TEquation = array [1..MaxN + 1] of Boolean;
	TEquations = array [1..MaxN] of TEquation;
	TAnswer = array [1..MaxN] of Boolean;
var
	N: TIndex;

function Solve(E: TEquations): Boolean;
var
	i, j, p, q: TIndex;
	HasValue: Boolean;
	Count: TIndex;
	Tmp: TEquation;
	Answer: TAnswer;
begin
	i := 1; //Current Equation
	j := 1; //Current Variable
	while (i <= N) and (j <= N) do
	begin
		HasValue := false;
		for p := i to N do
			if E[p, j] then
			begin
				HasValue := true;
				Tmp := E[i];
				E[i] := E[p];
				E[p] := Tmp;
				Break;
			end;
		if HasValue then
		begin
			for p := i + 1 to N do
				if E[p, j] then
					for q := j to N + 1 do
						E[p, q] := E[p, q] xor E[i, q];
			Inc(i);
		end;
		Inc(j);
	end;
	Result := false;
	for p := i to N do
		if E[p, N + 1] then Exit;
	Count := 0;
	FillChar(Answer, SizeOf(Answer), 0);
	for p := i - 1 downto 1 do
	begin
		for q := 1 to N do
			if E[p, q] then
			begin
				j := q;
				Break;
			end;
		Answer[j] := E[p, N + 1];
		for q := j + 1 to N do
			Answer[j] := Answer[j] xor (Answer[q] and E[p, q]);
		if not E[p, j] and Answer[j] then Exit;
		if Answer[j] then Inc(Count);
	end;
	Writeln(Count);
	for i := 1 to N do
		if Answer[i] then
			Write(i, ' ');
	Writeln;
	Result := true;
end;
