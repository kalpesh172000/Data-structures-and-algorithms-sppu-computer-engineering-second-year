public class Exp1ShellSort
{
    void display(int[] arr)
    {
        int len=arr.length;
        for(int i=0;i<len;i++)
        {
            System.out.print(arr[i]+ " " );
        }
    }
    int[] shellSort(int[] arr)
    {
        int len=arr.length;
        int gap=len/2;
        int i,j,temp;

        while(gap>0)
        {
            j=gap;
            while(j<len)
            {
                i=j-gap;
                while(i>=0)
                {
                    if(arr[i]>arr[i+gap])
                    {
                        temp=arr[i];
                        arr[i]=arr[i+gap];
                        arr[i+gap]=temp;
                    }
                    else
                    {
                        break;
                    }
                    i=i-gap;
                }
                j++;
            }
            gap=gap/2;
        }
        return arr;
    }
    public static void main(String[] args)
    {
        int[] arr={54,35,77,23,76,44,87};
        Exp1ShellSort sort=new Exp1ShellSort();
        System.out.print("Unsorted array: ");
        sort.display(arr);
        arr=sort.shellSort(arr);
        System.out.print("\nSorted array: ");
        sort.display(arr);
    }
}
