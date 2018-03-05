{
    luogu 3455
    莫比乌斯反演。
    注意对商做了分段加速，要对 μ 函数做前缀和。
}
const Size = 50000 + 5;

function min(x, y : int64) : int64;
begin
    if x < y then exit(x) else exit(y);
end;

type pInt = ^int64;
procedure flip(x, y : pInt);
var t : int64;
begin
    t := x^;
    x^ := y^;
    y^ := t;
end;

var
    prime : array[0..Size] of int64;
    np : array[0..Size] of boolean;
    mu : array[0..Size] of int64;
    sumMu : array[0..Size] of int64;

procedure eulerSieve;
var i, j, k : int64;
begin
    mu[1] := 1;
    for i := 2 to Size - 2 do
    begin
        if not np[i] then
        begin
            inc(prime[0]);
            prime[prime[0]] := i;
            mu[i] := -1;
        end;
        for j := 1 to prime[0] do
        begin
            k := i * prime[j];
            if k >= Size then break;
            np[k] := true;
            if i mod prime[j] = 0 then
            begin
                mu[k] := 0;
                break;
            end;
            mu[k] := -mu[i];
        end;
    end;
end;

var b, d, k, T, i, j, l, ans : int64;
begin
    read(T);

    eulerSieve();

    for i := 1 to Size - 2 do
        sumMu[i] := sumMu[i - 1] + mu[i];

    for i := 1 to T do
    begin
        read(b, d, k);
        b := b div k;
        d := d div k;
        if b > d then flip(@b, @d);

        ans := 0;
        j := 1;
        while j <= b do
        begin
            l := min(b div (b div j), d div (d div j));
            ans := ans + (sumMu[l] - sumMu[j - 1]) * (b div j) * (d div j);
            j := l + 1;
        end;
        writeln(ans);
    end;
end.
