<template>
  <div class="app">
    <el-card class="box-card">
      <template #header>
        <div class="clearfix">
          <span>创建房间</span>
        </div>
      </template>
      <div class="text item">
        <el-input v-model="roomnum1" class="num-input" />
        <el-button type="primary" @click="onCreate">立即创建</el-button>
      </div>
    </el-card>

    <el-card class="box-card">
      <template #header>
        <div class="clearfix">
          <span>进入房间</span>
        </div>
      </template>
      <div class="text item">
        <el-input v-model="roomnum2" class="num-input" />
        <el-button type="primary" @click="onEnter">立即进入</el-button>
      </div>
    </el-card>
  </div>
</template>
<script>
import Cookies from 'js-cookie'
export default {
  name: 'Main',
  data() {
    return {
      roomnum1: '',
      roomnum2: ''
    }
  },
  methods: {
    onCreate() {
      Cookies.set('room', this.roomnum1)
      Cookies.set('identity', 'owner')
      this.$router.push({ path: '/single' })
    },

    onEnter() {
      Cookies.set('room', this.roomnum2)
      this.$router.push({ path: '/single' })
    }
  }
}
</script>
<style scoped>
.app{
  top: 0;
  height: 100vh;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}
.box-card{
  width: 400px;
  margin-bottom: 30px;
}
.num-input{
  margin-bottom: 20px;
}
</style>
