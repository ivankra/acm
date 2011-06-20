program ASSL_BinaryHeap(Input, Output);
const
	MaxHeapSize = 1000;
	MaxDataRange = 1000;
type
	TIndex = Longint;
	TData = Longint;

	THeap = object
	private
		Size: TIndex;
		Data: array [1..MaxHeapSize] of TData;
		Map: array [1..MaxDataRange] of TIndex;

		function Compare(const DataA, DataB: TData): TData;
		procedure Swap(var DataA, DataB: TData);
		procedure Rise(Index: TIndex);
		procedure Sink(Index: TIndex);
	public
		procedure Push(Key: TData);
		function Pop: TData;
		function Delete(Key: TData): TData;
		function Top: TData;
	end;

function THeap.Compare(const DataA, DataB: TData): TData;
begin
	Result := DataA - DataB;
end;
procedure THeap.Swap(var DataA, DataB: TData);
var
	DataTmp: TData;
	MapTmp: TIndex;
begin
	DataTmp := DataA;
	DataA := DataB;
	DataB := DataTmp;
	MapTmp := Map[DataA];
	Map[DataA] := Map[DataB];
	Map[DataB] := MapTmp;
end;
procedure THeap.Push(Key: TData);
begin
	Inc(Size);
	Data[Size] := Key;
	Map[Key] := Size;
	Rise(Size);
end;
function THeap.Pop: TData;
begin
	Result := Data[1];
	Swap(Data[1], Data[Size]);
	Dec(Size);
	Sink(1);
end;
function THeap.Delete(Key: TData): TData;
var
	Index: TIndex;
begin
	Result := Key;
	Index := Map[Key];
	Key := Data[Size];
	Swap(Data[Index], Data[Size]);
	Dec(Size);
	Sink(Map[Key]);
	Rise(Map[Key]);
end;
function THeap.Top: TData;
begin
	Result := Data[1];
end;
procedure THeap.Rise(Index: TIndex);
var
	i: TIndex;
begin
	i := Index;
	while i > 1 do
	begin
		if Compare(Data[i shr 1], Data[i]) <= 0 then Break;
		Swap(Data[i shr 1], Data[i]);
		i := i shr 1;
	end;
end;
procedure THeap.Sink(Index: TIndex);
var
	i, j: TIndex;
begin
	i := Index;
	while i shl 1 <= Size do
	begin
		j := i shl 1;
		if (j < Size) and (Compare(Data[j + 1], Data[j]) < 0) then Inc(j);
		if Compare(Data[i], Data[j]) <= 0 then Break;
		Swap(Data[i], Data[j]);
		i := j;
	end;
end;

begin
end.



