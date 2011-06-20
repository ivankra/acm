const
  MAX_LEN = 30000;

type
  PNode = ^TNode;
  TNode = record
    child: array ['a' .. 'z'] of PNode;
    parent, link: PNode;
    symbol: char;
    final: boolean;
  end;

var
  n: integer;
  dict: array [1 .. MAX_LEN + 1] of string;
  s: string;
  root: PNode;
  answer: boolean;

procedure load;
var
  i: integer;
begin
  reset(input, 'input.txt');
  readln(n);
  for i := 1 to n do
    readln(dict[i]);
  readln(s);
end;

procedure makeNode(var node: PNode);
begin
  new(node);
  fillChar(node^, sizeOf(node^), 0);
end;

procedure solve;
var
  i, j, queueHead, queueTail: integer;
  curNode: PNode;
  queue: array [1 .. MAX_LEN] of PNode;
  ch: char;
begin
  makeNode(root);
  for i := 1 to n do
  begin
    curNode := root;
    for j := 1 to length(dict[i]) do
    begin
      if not assigned(curNode.child[dict[i][j]]) then
      begin
        makeNode(curNode.child[dict[i][j]]);
        curNode.child[dict[i][j]].parent := curNode;
        curNode.child[dict[i][j]].symbol := dict[i][j];
      end;
      curNode := curNode.child[dict[i][j]];
    end;
    curNode.final := true;
  end;
  queueHead := 1;
  queueTail := 1;
  queue[1] := root;
  while queueHead <= queueTail do
  begin
    curNode := queue[queueHead];
    inc(queueHead);
    if (curNode = root) or (curNode.parent = root) then
      curNode.link := root
    else curNode.link := curNode.parent.link.child[curNode.symbol];
    curNode.final := curNode.final or curNode.link.final;
    for ch := 'a' to 'z' do
      if assigned(curNode.child[ch]) then
      begin
        inc(queueTail);
        queue[queueTail] := curNode.child[ch];
      end
      else begin
        curNode.child[ch] := curNode.link.child[ch];
        if not assigned(curNode.child[ch]) then
          curNode.child[ch] := root;
      end;
  end;
  curNode := root;
  for i := 1 to length(s) do
  begin
    curNode := curNode.child[s[i]];
    if curNode.final then
      break;
  end;
  answer := curNode.final;
end;

procedure save;
begin
  rewrite(output, 'output.txt');
  writeln(answer);
end;

begin
  load;
  solve;
  save;
end.
