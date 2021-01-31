template<typename Bidirectional>
bool isPalindrome(Bidirectional first, Bidirectional last)
{
    while(true)
    {
        last--;
        if(first == last) //assume>= undefined
            break;
        if(*first != *last)
            return false;
        first++;
        if(first == last)
            break;
    }
    return true;
}
