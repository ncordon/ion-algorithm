# Ion Algorithm

Real coding metaheuristic modification for the subject Metaheuristicas, UGR, Granada

We took a recently developed metaheuristic physics-inspired called *Ion Motion Algorithm* (IMO), and the 20 first functions of [CEC2014](http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC2014/CEC2014.htm) competition. We had to improve the metaheuristic benchmarking those functions in 10 and 30 dimension.


## License
All the work is licensed in GPL, except the [function data](src/cec2014_data) and [definitions](src/cec2014_func.cpp) that weren't originally licensed by their author (no copyright violation intended, all the work done has educational purposes).

## Usage
In `src` folder, do `cmake .` and `make`. Realea software by Daniel Molina has been used, and the structure of the algorithm has been implemented in `metaheuristic.(h/cc)`. The parameters of the algorithm can be modified in `aux.h` and `aux.cc`. For further documentation check [memoria](doc/memoria.tex).

## Improvements

Original results of implementation of metaheuristic as described by their authors (such definition can be consulted in [memoria](doc/memoria.tex)):



|   |**D=10**|**D=30**|
|:--|-------:|-------:|
|f1|19084554.669857|78738913.351420|
|f2|16536.801547|13697676.211767|
|f3|21065.221623|77800.939852|
|f4|58.764875|246.343748|
|f5|20.170120|20.468675|
|f6|7.539682|34.790689|
|f7|0.861159|1.102618|
|f8|28.934028|129.837295|
|f9|26.123286|145.730468|
|f10|1157.285877|4219.909911|
|f11|1144.876264|4881.285910|
|f12|0.661762|1.304201|
|f13|0.456650|0.440387|
|f14|0.635537|0.260939|
|f15|4.164066|51.414376|
|f16|3.390798|12.366670|
|f17|236940.300926|3390125.155789|
|f18|6522.070266|110104.005591|
|f19|8.886340|32.516194|
|f20|13892.000148|53412.013643|

After the several improvements done:

|   |**D=10**|**D=30**|
|:--|:-------|:-------|
|f1|0.000000|153.994848|
|f2|0.000000|0.000000|
|f3|0.000000|0.000000|
|f4|0.000000|0.147572|
|f5|20.001247|20.622110|
|f6|0.000002|0.357917|
|f7|0.000000|0.000000|
|f8|4.576812|27.580246|
|f9|4.576811|27.699639|
|f10|283.681734|1693.500771|
|f11|299.088276|2233.018358|
|f12|0.029925|0.019306|
|f13|0.044096|0.169150|
|f14|0.275749|0.281541|
|f15|0.566455|2.281242|
|f16|3.267757|13.005128|
|f17|252.999183|1340.708149|
|f18|44.665859|286.135882|
|f19|1.593592|11.621429|
|f20|49.247290|505.252065|
