void fusion(int g, int m, int d, int* array)
{
    int i;
    int sg = g;
    int sd = m + 1;
    int* tmp = (int*)malloc((m - g + 1)*sizeof(int));

    for (i = g; i <= m; i++)
    {
        tmp[i - g] = array[i];
    }

    for (i = g; i <= d; i++)
    {
        if (sg == m + 1) break;
        else if (sd == d + 1 || tmp[sg - g] < array[sd])
        {
            array[i] = tmp[sg - g];
            sg++;
        }
        else 
        {
            array[i] = array[sd];
            sd++;
        }
    }
    free(tmp);
}

void tri_fusion_back(int g, int d, int* array)
{
    int m;
    
    if (g < d)
    {
        m = (g + d) / 2;
        tri_fusion_back(g, m, array);
        tri_fusion_back(m + 1, d, array);
        fusion(g, m, d, array);
    }
}

void tri_fusion(int* array, int arraysize) {
    int debut = 0;
    tri_fusion_back(debut, arraysize - 1, array);
}
