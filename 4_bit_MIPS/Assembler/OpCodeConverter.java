import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Scanner;

public class OpCodeConverter {
    public static String decimalToBinary(int num)
    {
        char[] binary = new char[4];
        for(int i=0;i<4;i++){
            binary[i]='0';
        }
        int id = 3;
        while (num > 0) {
            binary[id--] = (char) ('0'+(num % 2));
            num = num / 2;
        }
        return String.valueOf(binary);

    }
    public static HashMap<String,String[]> getHashMapForOpcode(){
        HashMap<Character,String[]> hashMap=new HashMap<>();
        String[][] strings=new String[][]{{"add","R"},{"addi","I"},{"sub","R"},{"subi","I"},{"and","R"},{"andi","I"},{"or","R"},{"ori","I"},
                {"sll","S"},{"srl","S"},{"nor","R"},{"lw","I"},{"sw","I"},{"beq","I"},{"bneq","I"},{"j","J"}};
        char ch='A';
        for(int i=0;i< strings.length;i++){
            hashMap.put(ch,strings[i]);
            ch++;
        }
        String input="BINHEKLMDCJOGPAF";
        HashMap<String,String[]> output=new HashMap<>();
        for(int i=0;i<input.length();i++){
            String[] string=hashMap.get(input.charAt(i));
            String[] value=new String[]{string[1],decimalToBinary(i)};
            output.put(string[0],value);
        }
        return output;
    }
    public static HashMap<String,String> getHashMapForRegister(){
        HashMap<String,String> hashMap=new HashMap<>();
        hashMap.put("$zero","0000");
        hashMap.put("$t0","0001");
        hashMap.put("$t1","0010");
        hashMap.put("$t2","0011");
        hashMap.put("$t3","0100");
        hashMap.put("$t4","0101");
        return hashMap;
    }
    public static HashMap<String,Integer> getHashMapForLabel() throws FileNotFoundException {
        Scanner scanner=new Scanner(new FileInputStream("input.txt"));
        HashMap<String,Integer> labelHashMap=new HashMap<>();
        int address=0;
        while (scanner.hasNextLine()){
            String string=scanner.nextLine();
            String[] ara1=string.split(" ");
            if(ara1.length==1){
                String label=string.substring(0,string.length()-1);
                labelHashMap.put(label,address);
                //System.out.println(label+": "+address);
                continue;
            }
            address++;
        }
        /*for (HashMap.Entry<String,Integer> set : labelHashMap.entrySet()) {
            System.out.println(set.getKey() + " = "+ set.getValue());
        }*/
        return labelHashMap;
    }
    public static void main(String[] args) {

        HashMap<String,String[]> output=getHashMapForOpcode();
        for (HashMap.Entry<String,String[]> set : output.entrySet()) {
            System.out.println(set.getKey() + " = "+ set.getValue()[0]+" "+set.getValue()[1]);
        }
    }
}
