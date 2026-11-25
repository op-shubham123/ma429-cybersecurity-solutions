"""Run from any directory with Python 3.8+ and g++ on PATH."""
from pathlib import Path
from tempfile import TemporaryDirectory
from subprocess import run, Popen, PIPE
from collections import Counter
from itertools import permutations
import random

ROOT = Path(__file__).resolve().parents[1]
rng = random.Random(429)

def check(build):
    def exe(p):
        return str(build / f"p{p:02d}")
    def output(p, data):
        return run([exe(p)], input=data, text=True, capture_output=True,
                   check=True, timeout=10).stdout.strip()
    def equal(p, data, want):
        got = output(p, data)
        assert got == want, (p, data, want, got)
    equal(1, "10 8 2\n1 2 3 5 6 7 8 9\n3 5\n", "2")
    equal(1, "3 2 1\n1 2\n3\n", "-1")
    for pieces, ok in [(["aca","aba","aba","cab","bac"], True),
                       (["abc","bCb","cb1","b13"], False),
                       (["aaa"]*7, True), (["aaa","bbb"], False)]:
        lines = output(3, str(len(pieces))+"\n"+"\n".join(pieces)).splitlines()
        assert lines[0] == ("YES" if ok else "NO")
        if ok:
            s = lines[1]
            assert Counter(s[i:i+3] for i in range(len(s)-2)) == Counter(pieces)
    equal(4,"4 4 2\n0 1 0 1\n1 2\n2 3\n3 4\n4 1","50")
    equal(4,"4 5 3\n7 1 7 2\n1 2\n2 3\n3 4\n4 1\n2 4","96")
    for cipher, words in [("ariksihsidlihcdnaehsetahgnisol",
            "Kira hates is he losing death childish L and Note"),
            ("iherehtolleh","HI Ho there HeLLo hello")]:
        found = output(5,f"{len(cipher)}\n{cipher}\n{len(words.split())}\n"+
                       "\n".join(words.split())).split()
        assert all(w in words.split() for w in found)
        assert "".join(w.lower()[::-1] for w in found)==cipher
    equal(6,"4\nab\naaaaaaaaaaa\nya\nklmbfxzb","1\n0\n24\n320092793")
    equal(7,"3\n1 2\n2 3","3")
    equal(7,"5\n1 2\n1 3\n1 4\n3 5","10")
    equal(8,"3 5\n2 3\n1 3\n1 2\n1 2\n1 2","YES\nYES\nNO\nYES\nNO")
    ops="1 1 2\n1 1 3\n1 3 4\n2 4\n2 5\n3\n2 1\n1 1 2\n1 3 2\n2 1\n3\n2 1"
    equal(9,"5 12 1\n"+ops,"4\n1\n1\n3\n1")
    equal(9,"5 12 2\n"+ops,"4\n1\n4\n4\n3")
    equal(9,"10 25 2\n1 9 3\n2 5\n1 1 3\n1 3 1\n2 2\n1 8 3\n1 5 6\n3\n1 9 2\n1 8 3\n2 9\n1 3 1\n2 5\n1 6 4\n3\n3\n2 4\n3\n1 10 9\n1 1 7\n3\n2 2\n3\n1 5 6\n1 1 4","1\n1\n5\n2\n1\n1")

    # Compare every possible labeling of small trees to the path DP.
    for n in range(2,8):
        edges=[(i,rng.randrange(i)) for i in range(1,n)]
        paths=[]
        for start in range(n):
            todo=[(start,-1,[])]
            while todo:
                u,parent,path=todo.pop()
                if u>start:
                    paths.append(path)
                for j,(a,b) in enumerate(edges):
                    if u in (a,b) and a+b-u!=parent:
                        todo.append((a+b-u,u,path+[j]))
        def score(labels):
            total=0
            for path in paths:
                present={labels[e] for e in path}
                total+=next(i for i in range(n) if i not in present)
            return total
        best=max(map(score,permutations(range(n-1))))
        equal(7,str(n)+"\n"+"\n".join(f"{a+1} {b+1}" for a,b in edges),str(best))

    def send(p, line):
        p.stdin.write(str(line)+"\n")
        p.stdin.flush()
    def finish(p):
        p.stdin.close()
        assert p.wait(timeout=5)==0
    cases=[(v,b,op) for v in [0,1,2,3,123456,(1<<30)-1]
           for b in (0,1) for op in ("&","|")]
    with Popen([exe(2)], stdin=PIPE, stdout=PIPE, text=True) as p:
        send(p,len(cases))
        for v,b,op in cases:
            x=int(p.stdout.readline())
            assert 0<=x<1<<30
            send(p,v&x if op=="&" else v|x)
            m=list(map(int,p.stdout.readline().split()))
            assert len(m)==2 and all(0<=i<1<<30 for i in m)
            send(p,m[b]^v)
            guess=int(p.stdout.readline())
            assert guess==b or (op=="&" and v==m[1] and x==1)
        finish(p)
    for f in [[1],[4,3,5,2,4,6],[2,4,2,2]] + [
            [rng.randint(1,n) for _ in range(n)] for n in range(2,40)]:
        n=len(f)
        with Popen([exe(10)],stdin=PIPE,stdout=PIPE,text=True) as p:
            send(p,n)
            queries=0
            while True:
                tag,c,r=p.stdout.readline().split()
                c,r=int(c),int(r)
                assert 1<=c<=n and 1<=r<=n
                h=r
                for _ in range(c):
                    h=f[h-1]
                if tag=="!":
                    assert h==c
                    break
                queries+=1
                assert tag=="?" and queries<=2
                send(p,h)
            finish(p)
    print("All checks passed.")

if __name__=="__main__":
    with TemporaryDirectory() as tmp:
        build=Path(tmp)
        for src in sorted((ROOT/"solutions").glob("*.cpp")):
            run(["g++","-std=c++17","-O2",str(src),"-o",str(build/src.stem)],check=True)
        check(build)
