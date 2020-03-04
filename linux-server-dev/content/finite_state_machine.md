# 有限状态机

有效状态机：
逻辑单元内部通常会使用到一种高效的编程方式：有限状态机(finite state machine)，有限状态机分成两种：状态独立的有限状态机和带状态转移的有限状态机
//状态独立的有限状态机
STATE_MACHINE( Package _pack )
{
    PackageType _type = _pack.GetType();
    switch( _type )
    {
        case Type _A:
            process_package_A( _pack );
            break;
        case Type _B:
            process_package_B( _pack );
            break;
    }
}
//带状态转移的有限状态机
STATE_MACHINE()
{
    State cur_State = type_A;
    while ( cur_State != type_C )
    {
        Package _pack = getNewPackage();
        switch( cur_State )
        {
            case type_A:
                process_package_state_A( _pack );
                cur_State = type_B;
                break;
            case type_B:
                process_package_state_B( _pack );
                cur_State = type_C;
                break;
        }
    }
}
状态机经常被用来解析HTTP请求
