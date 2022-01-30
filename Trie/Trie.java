import java.lang.*;
import java.util.*;
import javax.swing.*;   
import java.awt.event.*;
 
class TrieNode {
    TrieNode[] arr=new TrieNode[26];
    boolean isEnd;
    String data;
    
    public TrieNode() {
        
    }
 
}
 
public class Trie implements KeyListener{
   public JTextArea t1=new JTextArea(20,20);
   public JTextField t=new JTextField(20);
   static TrieNode root=new TrieNode();
  
    public Trie() {
        
    }
 
    // Inserts a word into the trie.
    public void insert(String word) {
        TrieNode p = root;
        for(int i=0; i<word.length(); i++){
            char c = word.charAt(i);
            int index = c-'a';
            if(p.arr[index]==null){
                TrieNode temp = new TrieNode();
                p.arr[index]=temp;
                p = temp;
            }else{
                p=p.arr[index];
            }
            if(p.data!=null)
            	p.data=p.data+","+word;
            else
            p.data=word;
        }
        p.isEnd=true;
    }
 
    // Returns if the word is in the trie.
    public boolean search(String word) {
        TrieNode p = searchNode(word);
        if(p==null){
            return false;
        }else{
            if(p.isEnd)
                return true;
        }
 
        return false;
    }
    public void keyPressed(KeyEvent e) {  
    
    	
    }  
    public void keyReleased(KeyEvent e) {  
    	startsWith(t.getText().toLowerCase());
    }  
    public void keyTyped(KeyEvent e) {
    	
    	
    }
 
    
    public boolean startsWith(String prefix) {
        TrieNode p = searchNode1(prefix);
        if(p==null){
            return false;
        }else{
            return true;
        }
    }
    public TrieNode searchNode1(String s){
        TrieNode p = root;
        String sug="";
        for(int i=0; i<s.length(); i++){
            char c= s.charAt(i);
            int index = c-'a';
            
            if(p.arr[index]!=null){
                p = p.arr[index];
            }else{
                return null;
            }
        }
 
        if(p==root)
            return null;
        else
        {
        	
        	
        	for(int i=0;i<26;i++)
        	{
        		if(p.arr[i]!=null)
        		{
        		sug=sug+p.arr[i].data+",";        		
        		}
        	}
        	System.out.println(sug);
        	t1.setText("");
        	t1.setText(sug);
        	
        		
        }
        return p;
    }
    
   
    public TrieNode searchNode(String s){
        TrieNode p = root;
        for(int i=0; i<s.length(); i++){
            char c= s.charAt(i);
            int index = c-'a';
            if(p.arr[index]!=null){
                p = p.arr[index];
            }else{
                return null;
            }
        }
 
        if(p==root)
            return null;
 
        return p;
    }
    
    public static void main(String args[])
    {
    	Trie obj=new Trie();
    	int i;
    	JFrame f;   
    	Trie y=new Trie();
    	String suggestions; 
    	JLabel l=new JLabel("Auto Suggestion Mode: ON");  
    	f=new JFrame("ComboBox Example");      	   
    	    
    	    obj.t.setBounds(190, 90, 140, 30);
    	    obj.t1.setBounds(40,140,440,40);
    	    obj.t.addKeyListener(obj);
    	    l.setBounds(180,50,150,20);
    	     
    	    f.add(obj.t);
    	    f.add(l);
    	    f.add(obj.t1);
    	    f.setLayout(null);    
    	    f.setSize(400,500);    
    	    f.setVisible(true);    
    	    
    	String str=new String();
    	Scanner s=new Scanner(System.in);
    	String a[]={"computer","compute","computation","computability","compact","compacted"};
    	for(i=0;i<a.length;i++)
    	{
    		obj.insert(a[i]);
    	}
    	while(true)
    	{
    		System.out.println("1.Insert 2.Search 3.Suggestions 4.Exit");
    		i=s.nextInt();
    		switch(i)
    		{
    		case 1:
    		{
    			str=s.next();
    			obj.insert(str);
    			break;
    		}
    		case 2:
    		{
    			str=s.next();
    			boolean b=obj.search(str);
    			System.out.println(str+" is found: "+b);
    			break;
    		}
    		case 3:
    		{
    			str=s.next();
    			obj.startsWith(str);
    			break;
    		}
    		case 4:
    		{
    			System.exit(1);
    			break;
    		}
    		}
    		
    	}
    }
}

