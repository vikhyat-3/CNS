import java.util.Scanner;

public class Main{
    public static String crc_calc(String message,String generator,int verify){
        int data[] = new int[message.length() + generator.length() - 1];
	    int divisor[] = new int[generator.length()];
	    for(int i=0;i<message.length();i++)
	    	data[i] = Integer.parseInt(message.charAt(i)+"");
	    for(int i=0;i<generator.length();i++)
	    	divisor[i] = Integer.parseInt(generator.charAt(i)+"");

	//Calculation of CRC
	    for(int i=0;i<message.length();i++)
	    {
	    	if(data[i]==1)
	    		for(int j=0;j<divisor.length;j++)
	    			data[i+j] ^= divisor[j];
	    }

	//Display CRC
	    String checksum="";
	    if(verify==0)
    	    for(int i=0;i<message.length();i++)
    	    	data[i] = Integer.parseInt(message.charAt(i)+"");
	    checksum="";
	    for(int i=0;i<data.length;i++) 
	    	checksum+=""+(data[i]);
	    return checksum;
    }
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);

	    //Input Data Stream
	    System.out.print("Enter message bits: ");
	    String message = sc.nextLine();
	    System.out.print("Enter generator: ");
	    String generator = sc.nextLine();
	    
        String ch1=crc_calc(message,generator,0);
        System.out.println(ch1);
	//Check for input CRC code
	    System.out.print("Enter checksum code: ");
		message = sc.nextLine();
		System.out.print("Enter generator: ");
		generator = sc.nextLine();
		String ch2=crc_calc(message,generator,1);
		for(int i=0;i<ch2.length();i++){
		    if(ch2.charAt(i)!='0')
		    {
		        System.out.println("INVALID");
		        return;
		    }
		}
		System.out.print("VALID");
		return;
	//Display validity of data
		
	
	}

}
