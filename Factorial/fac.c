#include <stdio.h>

long long fac_loop(int n, int k, long long prod);

long long fac(int n) { 
  return fac_loop(n,2,1); 
}

long long fac_loop(int n, int k, long long prod) { 
  if (k > n) 
    return prod; 
  else 
    return fac_loop(n, k+1, prod * (long long)k);
} 

/*
gcc -std=c99 fac.c -o fac
objdump -d fac 
0000000000400533 <fac_loop>:
  400533:	55                   	push   %rbp
  400534:	48 89 e5             	mov    %rsp,%rbp
  400537:	48 83 ec 10          	sub    $0x10,%rsp
  40053b:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40053e:	89 75 f8             	mov    %esi,-0x8(%rbp)
  400541:	48 89 55 f0          	mov    %rdx,-0x10(%rbp)
  400545:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400548:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  40054b:	7e 06                	jle    400553 <fac_loop+0x20>
  40054d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  400551:	eb 1f                	jmp    400572 <fac_loop+0x3f>
  400553:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400556:	48 98                	cltq   
  400558:	48 89 c2             	mov    %rax,%rdx
  40055b:	48 0f af 55 f0       	imul   -0x10(%rbp),%rdx
  400560:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400563:	8d 48 01             	lea    0x1(%rax),%ecx
  400566:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400569:	89 ce                	mov    %ecx,%esi
  40056b:	89 c7                	mov    %eax,%edi
  40056d:	e8 c1 ff ff ff       	callq  400533 <fac_loop>
  400572:	c9                   	leaveq 
  400573:	c3                   	retq   
*/


/* 
With Optimization
gcc -std=c99 fac.c -o fac -O2 
objdump -d fac
00000000004005c0 <fac_loop>:
  4005c0:	39 f7                	cmp    %esi,%edi
  4005c2:	48 89 d0             	mov    %rdx,%rax
  4005c5:	7c 22                	jl     4005e9 <fac_loop+0x29>
  4005c7:	29 f7                	sub    %esi,%edi
  4005c9:	31 c9                	xor    %ecx,%ecx
  4005cb:	48 63 f6             	movslq %esi,%rsi
  4005ce:	48 83 c7 01          	add    $0x1,%rdi
  4005d2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4005d8:	48 8d 14 31          	lea    (%rcx,%rsi,1),%rdx
  4005dc:	48 83 c1 01          	add    $0x1,%rcx
  4005e0:	48 0f af c2          	imul   %rdx,%rax
  4005e4:	48 39 f9             	cmp    %rdi,%rcx
  4005e7:	75 ef                	jne    4005d8 <fac_loop+0x18>
  4005e9:	f3 c3                	repz retq 
  4005eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
Tail call optimized

*/ 


int main(void) { 
  for (int i = 0; i < 100000; i ++) { 
    
    printf("%lld \n", fac(i));

  }

  return 0;
} 
