import java.util.*;
public class Main
{
	public static void main(String[] args) {
		System.out.println("Enter n value");
		Scanner sc=new Scanner(System.in);
		int n=sc.nextInt();
		System.out.println("Enter Number of packets");
		int p=sc.nextInt();
		int i=1;
		int count=4;
		System.out.println("Sender: Sending packets "+i+" to "+(i+3));
		for(;i<=p;i++){
		    System.out.println("\nReceiver: Enter acknowledgement to be sent ");
		    int ack=sc.nextInt();
		    if(ack!=(i+4)){
		        System.out.println("\nSender: Error in acknowledgement\nResending packets :");
		        for(int j=i,c=1;j<=p&&c<=4;j++,c++){
		            System.out.print(j+" ");
		            count++;
		        }
		        i--;
		    }
		    else{
		        if(i==p)
		            break;
		        if((i+4)<=p){
		            System.out.println("\nSending packet "+(i+4));
		            count++;
		        }
		    }
		}
		System.out.println("\nALL PACKETS SENT AND ACKNOWLEDGED SUCCESSFULLY!");
		System.out.println("\nTOTAL PACKETS SENT: "+count);
	}
}
