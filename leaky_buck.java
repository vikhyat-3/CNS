import java.util.*;
public class Main {

	public static void main(String[] args) {
		System.out.println("Enter number of packets");
		Scanner sc =new Scanner(System.in);
		int n=sc.nextInt();
		int p[]=new int[n];
		System.out.println("Enter the packet arrival time intervals");
		for(int i=0;i<n;i++)
			p[i]=sc.nextInt();
		System.out.println("Enter I(PACKET TIME) and L(BUCKET CAPACITY)");
		int i=sc.nextInt();
		int l=sc.nextInt();
		int lct=p[0];
		int x=0,current_buck=0;
		for(int j=0;j<n;j++) {
			current_buck=x-p[j]+lct;
			if(current_buck>l) {
				System.out.println("Packet non-conforming is: "+p[j]);
			}
			else {
				x=current_buck+i;
				lct=p[j];
				System.out.println("Packet conforming is: "+p[j]);
			}
		}
	}
}
