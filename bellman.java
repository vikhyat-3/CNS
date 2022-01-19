package bellman;

import java.util.*;
public class bellford {
	public static void bellman(int a[][],int d[],int src,int n) {
		int min=Integer.MAX_VALUE;
		System.out.println(Integer.MAX_VALUE);
		for(int i=0;i<n-1;i++) {
			for(int j=0;j<n;j++) {
				min=Integer.MAX_VALUE;
				System.out.println(min);
				for(int k=0;k<n;k++)
				{
					if(min>(a[j][k]+d[k])) {
						System.out.println(""+min+" "+a[j][k]+"  "+d[k]);
						min=a[j][k]+d[k];
					}
				}
				d[j]=min;
				System.out.println("Min is"+min);
			}
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int n,src;
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter no. of vertices");
		n=sc.nextInt();
		int a[][]=new int[n][n];
		System.out.println("Enter source vertex");
		src=sc.nextInt();
		System.out.println("Enter the adjacency matrix");
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				a[i][j]=sc.nextInt();
				
		int distance[]=new int[n];
		for(int i=0;i<n;i++) 
			distance[i]=999;
		distance[src-1]=0;
		for(int i=0;i<n;i++)
			System.out.println(distance[i]);
		bellman(a,distance,src,n);
		for(int i=0;i<n;i++) {
			if(i==(src-1))
				continue;
			System.out.println("Distance of "+src+" from "+(i+1)+" is "+distance[i]);
		}
	}

}
