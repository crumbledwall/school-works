<template>
  <div>
    <Nav />
    <h1 id="topic"></h1>
    <div class="main">
    <el-button class="button" @click="sleep">sleep</el-button>
    <el-button class="button" @click="add">add</el-button>
    <el-button class="button" @click="change">change</el-button>
    
    <el-button class="button" @click="deletethis">delete</el-button>
    </div>
    <video class="video" width="320" height="240" controls>
  <source src="https://www.runoob.com/try/demo_source/movie.mp4" type="video/mp4">
  您的浏览器不支持 HTML5 video 标签。
</video>
  </div>
</template>

<script>

import Nav from '../../components/Nav'
export default {
  name: 'index',
  components: {
    Nav
  },
  methods: {
    sleep: function () {
      setTimeout(() => { alert('sleep!') }, 2000)
    },
    change: function() {
      document.getElementById("topic").textContent = "i changed!"
    },
    add: function () {
      document.getElementById("topic").textContent = "i added!"
    },
    deletethis: function () {
      document.getElementById("topic").textContent = ""
    }
  }
}
</script>
<style scoped>
#topic {
  margin-top: 100px;
}
.video{
  margin-top: 30px;
}
</style>
