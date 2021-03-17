<template>
  <div>
    <Nav />
    <div class="covers">
      <el-row>
        <el-col :span="24" v-for='img in imgData' :key='img.url'>
          <div class="coverdiv">
            <Cover class="coveritem" :imgsrc="img.url" :imgalt="img.name" :imgdetail="img.detail" />
          </div>
        </el-col>
      </el-row>
    </div>
  </div>
</template>

<script>
import Nav from '../../components/Nav'
import Cover from '../../components/Cover'

export default {
  name: 'catagery',
  data(){
    return{
      imgData: [
        {
          "url": require("../../assets/IMG_7540.jpg"),
          "name": "居家",
          "detail": "寒冷的冬日还是宅在家里比较好"
        },
        {
          "url": require("../../assets/IMG_7541.jpg"),
          "name": "原野",
          "detail": "原野的远处被落日的余辉染红"
        },
        {
          "url": require("../../assets/IMG_7542.jpg"),
          "name": "密境",
          "detail": "密境的深处是各种自在生灵的乐土"
        },
        {
          "url": require("../../assets/IMG_7543.jpg"),
          "name": "城市",
          "detail": "大都市的繁华使人留恋"
        }
      ]
    }
  },
  methods:{

  },
  components: {
    Nav,
    Cover
  }
}
</script>

<style scoped>
  .coveritem{
    position: absolute;
    margin: 0 auto;
    top:0;
    right: 0;
    left: 0;
  }
  .covers{
    padding-top: 70px;
    margin: 0 auto;
    width: 500px;
    height: 600px;
  }
  .coverdiv{
    position: relative;
  }
  .el-col-24{
    padding-bottom: 300px;
  }

</style>
    
